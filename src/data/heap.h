// Forward declarations

class heap;

#if !defined(__forward__) && !defined(__nobb__data__heap__h)
#define __nobb__data__heap__h

// Libraries

#include <iostream>

// Includes

#include "event/event.h"

class heap
{
  // Members

  size_t _size;
  event ** _events;

public:
  // Constructors

  heap();

  // Destructor

  ~heap();

  // Getters

  const size_t & size();

  // Methods

  void push(event *);

  event * peek();
  event * pop();

private:
  // Private methods

  void swap(const size_t &, const size_t &);
  void bubble_up(const size_t &);
  void bubble_down(const size_t &);

  // Static members
  struct settings{
    static constexpr size_t capacity = 100000; // TODO: change it!
  };
};

#endif
