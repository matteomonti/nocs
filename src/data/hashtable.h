// Forward declarations

template <typename, typename> class hashtable;

#if !defined(__forward__) && !defined(__nobb__data__hashtable__h)
#define __nobb__data__hashtable__h

// Libraries

#include <stdint.h>
#include <stddef.h>
#include <type_traits>
#include <assert.h>

template <typename ktype, typename vtype> class hashtable
{
public:

  // Settings

  static constexpr size_t expand_threshold = 2;
  static constexpr size_t contract_threshold = 8;
  static constexpr size_t min_alloc = 32;

  // Service nested classes

  struct item
  {
    bool active;
    ktype key;
    vtype value;
  };

  // Members

  item * _items;
  size_t _size;
  size_t _alloc;

public:

  // Constructors

  hashtable();

  // Destructor

  ~hashtable();

  // Methods

  void add(const ktype &, const vtype &);
  void remove(const ktype &);

  template <typename lambda> void each(const lambda &) const;

private:

  // Private methods

  size_t slot(const ktype &) const;
  void realloc(const size_t &);

public:

  // Operators

  const vtype & operator [] (const ktype &) const;

private:

  // Private static methods

  template <typename type, typename std :: enable_if <sizeof(type) == 4> :: type * = nullptr> static size_t hash(const type &);
  template <typename type, typename std :: enable_if <sizeof(type) == 8> :: type * = nullptr> static size_t hash(const type &);
};

#endif
