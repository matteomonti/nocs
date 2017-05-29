#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <iomanip>

#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "graphics/window.h"


double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
  srand(time(nullptr));

  molecule alpha
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.1, 0.1},
    {rnd1(), rnd1()},
    0,
    M_PI
  );

  molecule beta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.2, 0.2},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule gamma
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.3, 0.3},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule delta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.4, 0.4},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule epsilon
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.5, 0.5},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule zeta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.6, 0.6},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  engine engine(4);

  engine.add(alpha);
  engine.add(beta);
  engine.add(gamma);
  engine.add(delta);
  engine.add(epsilon);
  engine.add(zeta);

  window my_window;

  for(double t = 0;; t += 0.1)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    double energy = 0.;

    engine.each <molecule> ([&](const molecule & alpha)
    {
      energy += alpha.energy();
      engine.each <molecule> ([&](const molecule & beta)
      {
        if(alpha.tag.id() == beta.tag.id())
          return;

        for(size_t i = 0; i < alpha.size(); i++)
          for(size_t j = 0; j < beta.size(); j++)
          {
            vec xa = alpha.position() + alpha[i].position() % alpha.orientation();
            vec xb = beta.position() + beta[j].position() % beta.orientation();

            if(!(xa - xb) < alpha[i].radius() + beta[i].radius() - 1.e-6)
            {
              std :: cout << "Compenetration found!" << std :: endl;
              window :: wait_click();
            }
          }
      });
    });

    std :: cout << std :: setw(6) << std :: setprecision(1) << std :: fixed << t << ": " << energy << std :: endl;
  }
}

#endif
