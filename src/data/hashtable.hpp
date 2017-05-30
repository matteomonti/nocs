#ifndef __nobb__data__hashtable__hpp
#define __nobb__data__hashtable__hpp

#include "hashtable.h"

// Constructors

template <typename ktype, typename vtype> hashtable <ktype, vtype> :: hashtable() : _items(new item[min_alloc]), _size(0), _alloc(min_alloc)
{
  for(size_t i = 0; i < this->_alloc; i++)
    this->_items[i].active = false;
}

// Destructor

template <typename ktype, typename vtype> hashtable <ktype, vtype> :: ~hashtable()
{
  delete [] this->_items;
}

// Methods

template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: add(const ktype & key, const vtype & value)
{
  if(this->_alloc / (this->_size + 1) < expand_threshold)
    this->realloc(this->_alloc * 2);

  size_t index = hash(key) % this->_alloc;

  while(this->_items[index].active)
    index = (index + 1) % this->_alloc;

  this->_items[index].active = true;
  this->_items[index].key = key;
  this->_items[index].value = value;

  this->_size++;
}

template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: remove(const ktype & key)
{
  size_t i = this->slot(key);

  if(this->_alloc / (this->_size + 1) > contract_threshold && this->_alloc > min_alloc)
  {
    this->_items[i].active = false;
    this->realloc(this->_alloc / 2);
  }
  else
  {
    size_t j = i;
    size_t k;

    while(true)
    {
      this->_items[i].active = false;

      do
      {
        j = (j + 1) % this->_alloc;

        if(!(this->_items[j].active))
          goto end;

        k = hash(this->_items[j].key) % this->_alloc;
      } while((i <= j) ? ((i < k) && (k <= j)) : ((i < k) || (k <= j)));

      this->_items[i] = this->_items[j];
      i = j;
    }

    end:;
    this->_size--;
  }
}

template <typename ktype, typename vtype> template <typename lambda> void hashtable <ktype, vtype> :: each(const lambda & callback) const
{
  for(size_t i = 0; i < this->_alloc; i++)
    if(this->_items[i].active)
      callback(this->_items[i].value);
}

// Private methods

template <typename ktype, typename vtype> size_t hashtable <ktype, vtype> :: slot(const ktype & key) const
{
  size_t index = hash(key) % this->_alloc;
  assert(this->_items[index].active);

  while(this->_items[index].key != key)
  {
    index = (index + 1) % this->_alloc;
    assert(this->_items[index].active);
  }

  return index;
}

template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: realloc(const size_t & alloc)
{
  item * old = this->_items;

  size_t old_alloc = this->_alloc;
  this->_alloc = alloc;

  this->_size = 0;
  this->_items = new item[this->_alloc];

  for(size_t i = 0; i < this->_alloc; i++)
    this->_items[i].active = false;

  for(size_t i = 0; i < old_alloc; i++)
    if(old[i].active)
      this->add(old[i].key, old[i].value);

  delete [] old;
}

// Operators

template <typename ktype, typename vtype> const vtype & hashtable <ktype, vtype> :: operator [] (const ktype & key) const
{
  return this->_items[this->slot(key)].value;
}

// Private methods

template <typename ktype, typename vtype> template <typename type, typename std :: enable_if <sizeof(type) == 4> :: type *> size_t hashtable <ktype, vtype> :: hash(const type & item)
{
  uint32_t key = *(reinterpret_cast <const uint32_t *> (&item));

  int prime = 0x27d4eb2d;
  key = (key ^ 61) ^ (key >> 16);
  key = key + (key << 3);
  key = key ^ (key >> 4);
  key = key * prime;
  key = key ^ (key >> 15);

  return key;
}

template <typename ktype, typename vtype> template <typename type, typename std :: enable_if <sizeof(type) == 8> :: type *> size_t hashtable <ktype, vtype> :: hash(const type & item)
{
  uint64_t key = *(reinterpret_cast <const uint64_t *> (&item));

  key = (~key) + (key << 21);
  key = key ^ (key >> 24);
  key = (key + (key << 3)) + (key << 8);
  key = key ^ (key >> 14);
  key = (key + (key << 2)) + (key << 4);
  key = key ^ (key >> 28);
  key = key + (key << 31);

  return key;
}

#endif
