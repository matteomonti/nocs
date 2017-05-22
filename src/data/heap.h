// Forward declarations

template <typename> class heap;

#if !defined(__forward__) && !defined(__nobb__data__heap__h)
#define __nobb__data__heap__h

// Libraries

#include <stdint.h>

template <typename type> class heap
{
  // Settings

  static constexpr size_t first_alloc = 16;

  // Members

  type * _items;
  size_t _size;
  size_t _alloc;

public:

  // Constructors

  heap();

  // Destructor

  ~heap();

  // Getters

  const size_t & size() const;

  // Methods

  void push(const type &);

  const type & peek() const;
  type pop();

private:

  // Private methods

  void swap(const size_t &, const size_t &);
  void bubble_up(const size_t &);
  void bubble_down(const size_t &);
};

#endif
