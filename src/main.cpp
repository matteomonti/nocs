#ifdef __main__

#include <iostream>

#include "graphics/lockpick.h"

int main()
{
  lockpick :: window my_window("My pretty window!");
  my_window.line({0, 0}, {1, 1});
  my_window.flush();
  lockpick :: window :: wait_click();
}

#endif
