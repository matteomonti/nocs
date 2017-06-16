#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <iomanip>

#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "elements/bumper.h"
#include "graphics/window.h"

enum {small, big};

double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
  srand(0);

  engine engine(4);

  std :: cout << "SMALL IS " << small << std :: endl;
  std :: cout << "BIG IS " << big << std :: endl;

  molecule small1
  (
    {
      {{0, 0}, 1, 0.025},
      {{0, 0.05}, 1, 0.025}
    },
    {0.1, 0.2},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  size_t small1id = engine.add(small1);
  engine.tag(small1id, small);

  molecule small2
  (
    {
      {{0, 0}, 1, 0.025},
      {{0, 0.05}, 1, 0.025}
    },
    {0.1, 0.8},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  size_t small2id = engine.add(small2);
  engine.tag(small2id, small);

  molecule big1
  (
    {
      {{0, 0}, 1, 0.05}
    },
    {0.5, 0.5},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  size_t big1id = engine.add(big1);
  engine.tag(big1id, big);

  molecule big2
  (
    {
      {{0, 0}, 1, 0.05}
    },
    {0.5, 0.8},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  size_t big2id = engine.add(big2);
  engine.tag(big2id, big);

  bumper bumpy
  {
    {0.5, 0.2},
    0.2
  };

  engine.add(bumpy);

  engine.each <molecule> ([&](const molecule & molecule)
  {
    std :: cout << molecule.tag.id() << " (" << (size_t) molecule.tag[0] << ")" << std :: endl;
  });

  size_t handle = engine.on <events :: bumper> ([](const report <events :: bumper> & report)
  {
    std :: cout << "Collision between " << report.id() << " and bumper" << std :: endl;
  });

  window my_window;

  my_window.draw(engine);
  window :: wait_click();

  bool removed = false;

  for(double t = 0;; t += 0.03)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    if(t > 100 && !removed)
    {
      std :: cout << "Unsubscribing!" << std :: endl;
      engine.unsubscribe <events :: bumper> (handle);
      removed = true;
    }

    usleep(1.e4);
  }
}

#endif
