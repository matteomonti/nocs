#ifndef __nobb__data__set__hpp
#define __nobb__data__set__hpp

#include "set.h"

// Constructors

template <typename type> set <type> :: set() : _items(new type [first_alloc]), _size(0), _alloc(first_alloc)
{
}

// Destructor

template <typename type> set <type> :: ~set()
{
  delete [] this->_items;
}

// Methods

template <typename type> void set <type> :: add(const type & item)
{
  if(this->_size == this->_alloc)
  {
    type * old = this->_items;
    this->_alloc *= 2;
    this->_items = new type [this->_alloc];

    for(size_t i = 0; i < this->_size; i++)
      this->_items[i] = old[i];

    delete [] old;
  }

  this->_items[this->_size++] = item;
}

template <typename type> void set <type> :: remove(const type & item)
{
  size_t cursor = 0;
  size_t skip = 0;

  for(cursor = 0; skip + cursor < this->_size; cursor++)
  {
    while(this->_items[cursor + skip] == item)
      skip++;

    this->_items[cursor] = this->_items[cursor + skip];
  }

  this->_size = cursor;
}

template <typename type> template <typename lambda, typename std :: enable_if <set <type> :: template valid <lambda> :: value> :: type *> void set <type> :: each(const lambda & callback)
{
  for(size_t i = 0; i < this->_size; i++)
    callback(this->_items[i]);
}

#endif
