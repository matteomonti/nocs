#ifdef __main__

#include <iostream>

#include "data/hashtable.hpp"

int main()
{
  srand(time(nullptr));

  hashtable <int, int> my_hashtable;

  for(size_t n = 0;; n++)
  {
    if(n % 1000000 == 0)
      std :: cout << n << std :: endl;

    int keys[16];

    for(size_t i = 0; i < 16; i++)
      keys[i] = rand();

    for(size_t i = 0; i < 16; i++)
      my_hashtable.add(keys[i], i);

    my_hashtable.remove(keys[0]);

    for(size_t i = 15; i >= 1; i--)
    {
      assert(my_hashtable[keys[i]] == i);
      my_hashtable.remove(keys[i]);
    }
  }
}

#endif
