#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <iomanip>

#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "elements/bumper.h"
#include "graphics/window.h"

double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
  srand(0);

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

  bumper bumpy_bumpy
  (
    {0.6, 0.6},
    0.2
  );

  engine engine(4);

  engine.on <events :: bumper> ([](const report <events :: bumper> & report)
  {
    std :: cout << "Bumper event between molecule " << report.id() << " and a bumper." << std :: endl;

    std :: cout << "General info about " << report.id() << ":" << std :: endl
    << "Velocity before:\t" << report.velocity.before() << std :: endl
    << "Velocity after:\t" << report.velocity.after() << std :: endl
    << "Delta Velocity:\t" << report.velocity.delta() << std :: endl
    << "Momentum before:\t" << report.momentum.before() << std :: endl
    << "Momentum after:\t" << report.momentum.after() << std :: endl
    << "Delta Momentum:\t" << report.momentum.delta() << std :: endl
    << "Angular_velocity before:\t" << report.angular_velocity.before() << std :: endl
    << "Angular_velocity after:\t" << report.angular_velocity.after() << std :: endl
    << "Delta Angular_velocity:\t" << report.angular_velocity.delta() << std :: endl
    << "angular_momentum before:\t" << report.angular_momentum.before() << std :: endl
    << "angular_momentum after:\t" << report.angular_momentum.after() << std :: endl
    << "Delta angular_momentum:\t" << report.angular_momentum.delta() << std :: endl
    << "energy before:\t" << report.energy.before() << std :: endl
    << "energy after:\t" << report.energy.after() << std :: endl
    << "Delta energy:\t" << report.energy.delta() << std :: endl
    << "Atom involved:\t" << report.atom() << std :: endl
    << "Molecule mass:\t" << report.mass() << std :: endl << std :: endl;

    std :: cout << "General info about bumper:" << std :: endl
    << "Position: " << report.bumper.position() << std :: endl
    << "Radius: " << report.bumper.radius() << std :: endl << std :: endl;

  });

  engine.on <events :: molecule> ([](const report <events :: molecule> & report)
  {
    std :: cout << "Molecule event between " << report.alpha.id() << " and " << report.beta.id() << std :: endl << std :: endl;

    std :: cout << "General info about " << report.alpha.id() << ":" << std :: endl
    << "Velocity before:\t" << report.alpha.velocity.before() << std :: endl
    << "Velocity after:\t" << report.alpha.velocity.after() << std :: endl
    << "Delta Velocity:\t" << report.alpha.velocity.delta() << std :: endl
    << "Momentum before:\t" << report.alpha.momentum.before() << std :: endl
    << "Momentum after:\t" << report.alpha.momentum.after() << std :: endl
    << "Delta Momentum:\t" << report.alpha.momentum.delta() << std :: endl
    << "Angular_velocity before:\t" << report.alpha.angular_velocity.before() << std :: endl
    << "Angular_velocity after:\t" << report.alpha.angular_velocity.after() << std :: endl
    << "Delta Angular_velocity:\t" << report.alpha.angular_velocity.delta() << std :: endl
    << "angular_momentum before:\t" << report.alpha.angular_momentum.before() << std :: endl
    << "angular_momentum after:\t" << report.alpha.angular_momentum.after() << std :: endl
    << "Delta angular_momentum:\t" << report.alpha.angular_momentum.delta() << std :: endl
    << "energy before:\t" << report.alpha.energy.before() << std :: endl
    << "energy after:\t" << report.alpha.energy.after() << std :: endl
    << "Delta energy:\t" << report.alpha.energy.delta() << std :: endl
    << "Atom involved:\t" << report.alpha.atom() << std :: endl
    << "Molecule mass:\t" << report.alpha.mass() << std :: endl << std :: endl;

    std :: cout << "General info about " << report.beta.id() << ":" << std :: endl
    << "Velocity before:\t" << report.beta.velocity.before() << std :: endl
    << "Velocity after:\t" << report.beta.velocity.after() << std :: endl
    << "Delta Velocity:\t" << report.beta.velocity.delta() << std :: endl
    << "Momentum before:\t" << report.beta.momentum.before() << std :: endl
    << "Momentum after:\t" << report.beta.momentum.after() << std :: endl
    << "Delta Momentum:\t" << report.beta.momentum.delta() << std :: endl
    << "Angular_velocity before:\t" << report.beta.angular_velocity.before() << std :: endl
    << "Angular_velocity after:\t" << report.beta.angular_velocity.after() << std :: endl
    << "Delta Angular_velocity:\t" << report.beta.angular_velocity.delta() << std :: endl
    << "angular_momentum before:\t" << report.beta.angular_momentum.before() << std :: endl
    << "angular_momentum after:\t" << report.beta.angular_momentum.after() << std :: endl
    << "Delta angular_momentum:\t" << report.beta.angular_momentum.delta() << std :: endl
    << "energy before:\t" << report.beta.energy.before() << std :: endl
    << "energy after:\t" << report.beta.energy.after() << std :: endl
    << "Delta energy:\t" << report.beta.energy.delta() << std :: endl
    << "Atom involved:\t" << report.beta.atom() << std :: endl
    << "Molecule mass:\t" << report.beta.mass() << std :: endl << std :: endl;

  });

  engine.add(alpha);
  engine.add(beta);
  engine.add(gamma);
  engine.add(delta);

  engine.add(bumpy_bumpy);

  window my_window;

  for(double t = 0;; t += 0.03)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    usleep(1.e4);
  }
}

#endif
