#ifdef __main__

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "engine/engine.hpp"
#include "graphics/window.h"

int main()
{
  std :: cout << "At least it starts?" << std :: endl; 
  enum tags {fatty, ninja};

  graphics::window my_window; // Just a window

  engine my_engine(6); // 6x6 zones

  for(double x = 0.1; x <= 0.9; x += 0.1)
    for(double y = 0.1; y <= 0.4; y += 0.1)
    {
      molecule my_molecule
      (
        { // Array of atoms
          {{0., 0.}, 1., 0.005}, // Position (arbitrary reference system), mass, radius
          {{0., 0.02}, 10., 0.015}
        },
        {x, y}, // Position of center of mass
        {0, 0}, // Velocity of center of mass
        0., // Initial orientation (in radians)
        M_PI / 4. // Angular velocity (in radians / time unit)
      );

      size_t my_molecule_id = my_engine.add(my_molecule); // Now the molecule is in your engine, ready to work
      my_engine.tag(my_molecule_id, fatty); // Adds tag fatty to the first molecule. Note that you can add tags only after inserting them in the engine.
    }

  double swap = 1.;

  for(double x = 0.1; x <= 0.9; x += 0.1)
    for(double y = 0.6; y <= 0.9; y += 0.1)
    {
      molecule my_other_molecule // Same thing as before
      (
        {
          {{0., 0.}, 0.01, 0.02}
        },
        {x, y},
        {3. * swap, 3. * swap},
        0.,
        0.
      );

      swap *= -1; // This serves the purpose to have a null total momentum

      size_t my_other_molecule_id = my_engine.add(my_other_molecule); // Same for the other
      my_engine.tag(my_other_molecule_id, ninja); // Same thing for the other molecule
    }

  bumper my_bumper({0.5, 0.5}, 0.03);
  my_engine.add(my_bumper);

  my_engine.elasticity(fatty, fatty, 0.8);

  my_window.draw(my_engine); // Draw the content of the engine on the window
  my_window.wait_click(); // Guess what

  my_engine.on <events :: molecule> (fatty, ninja, [&](const report <events :: molecule> my_report)
  {
    std :: cout << "There has been a collision between " << my_report.alpha.id() << " and " << my_report.beta.id() << std :: endl;
    std :: cout << "Delta energy for alpha: " << my_report.alpha.energy.delta() << std :: endl;
  });

  for(double time = 0.;; time += 0.01)
  {
    my_engine.run(time); // Run UNTIL time

    double fatty_total_energy = 0.;

    my_engine.each <molecule> (fatty, [&](const molecule & current_molecule) // Dear engine, for each molecule with tag fatty, please execute this lambda that accepts a const reference
                                                                             // to the current molecule and captures fatty_total_energy. Each time it is called the lambda adds to
                                                                             // fatty_total_energy the energy of the current molecule. Also known as: sum the energies of all the fatty molecules.
    {
      fatty_total_energy += current_molecule.energy();
    });

    double ninja_total_energy = 0.;

    my_engine.each <molecule> (ninja, [&](const molecule & current_molecule)
    {
      ninja_total_energy += current_molecule.energy();
    });
    std :: cout << std :: setw(10) << fatty_total_energy << std :: setw(10) << ninja_total_energy << std :: endl;

    my_engine.reset.energy.tag(ninja, 1.);

    my_window.draw(my_engine);
  }
}

#endif
