#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "data/set.hpp"

int main()
{
  set <int> s;

  for(int i = 0; i < 8; i++)
  {
    while(rand() % 4 != 0)
      s.add(4);

    s.add(i);
  }

  s.each([](int n)
  {
    std :: cout << n << std :: endl;
  });

  std :: cout << std :: endl << std :: endl;

  s.remove(4);

  s.each([](int n)
  {
    std :: cout << n << std :: endl;
  });
}

#endif
