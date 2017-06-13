#ifdef __main__

#include <iostream>

#include "callback/dispatcher.h"

template <typename lambda> callback <events :: molecule, lambda> * make_callback(const lambda & callback)
{
  return new :: callback <events :: molecule, lambda> (callback);
}

int main()
{
  dispatcher my_dispatcher;

  size_t first_dispatcher = my_dispatcher.add(make_callback([]()
  {
    std :: cout << "Yay! Ci sono!" << std :: endl;
  }));

  size_t second_dispatcher = my_dispatcher.add(make_callback([]()
  {
    std :: cout << "Yay! Pure io!" << std :: endl;
  }));

  my_dispatcher.trigger(*((events :: molecule *) nullptr));
  my_dispatcher.remove <events :: molecule> (first_dispatcher);
  my_dispatcher.trigger(*((events :: molecule *) nullptr));
}

#endif
