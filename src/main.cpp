#ifdef __main__

#include <iostream>
#include <iomanip>
#include <random>

#include <fstream>

#include "engine/engine.hpp"
#include "graphics/window.h"


int main()
{
  // Setup File Stream

  std :: ofstream oeb("/home/carlidel/Scrivania/output_event_based.txt");
  oeb << "Time \t Position \t Orientation \t Momentum \t Angluar Momentum \t Delta Momentum \t Delta Angular Momentum" << std :: endl;
  oeb.precision(6);
  oeb.setf( std::ios::fixed, std:: ios::floatfield );

  std :: ofstream otb("/home/carlidel/Scrivania/output_time_based.txt");
  otb << "Time \t Id \t Position \t Orientation \t Velocity \t Angular Velocity" << std :: endl;
  otb.precision(6);
  otb.setf( std::ios::fixed, std:: ios::floatfield );

  // Setup Random Generator

  double lower_bound = -1;
  double upper_bound = 1;

  std :: uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std :: default_random_engine re;

  // Tags

  enum tags {simple, complex};

  // Initialization

  engine my_engine(10);
  window my_window;

  // Wind Breaker!

  bumper wind_breaker({0., 0.}, 0.005);
  my_engine.add(wind_breaker);

  // Simple molecules

  double diameter = 0.01;

  for(double x = 0.015; x < 0.83; x += diameter * 2)
    for(double y = 0.015; y <= 0.995; y += diameter * 2)
    {
      molecule first
      (
        {
          {{0., 0.}, 1., diameter / 2}
        },
        {x, y},
        {unif(re), unif(re)},
        0.,
        0
      );

      size_t molecule_id = my_engine.add(first);
      my_engine.tag(molecule_id, simple);
    }

  // PENIS ONE !!!

  diameter *= 3;

  molecule second
  (

      {
        {{0., 0.}, 2., diameter / 2},
        {{0., diameter}, 2., diameter / 2},
        {{0., -diameter}, 2., diameter / 2},
        {{diameter, 0.}, 2., diameter / 2},
        {{diameter * 2, 0.}, 2, diameter / 2},
        {{diameter * 3, 0.}, 2, diameter / 2},
        {{diameter * 4, 0.}, 2, diameter / 2},
      },
      {0.9, 0.5},
      {0,0},
      M_PI / 2,
      0
  );

  // Event-Based Data Gathering (works for single molecule)

  size_t id_complex = my_engine.add(second);
  my_engine.tag(id_complex, complex);

  my_engine.on <events :: molecule>
  (
    complex,
    [&](const report <events :: molecule> rep)
    {
      // Time - Position - Orientation - Momentum - Angluar Momentum - Delta Momentum - Delta Angular Momentum.
      if(rep.alpha.id() == id_complex)
      {
        oeb << rep.time() << "\t" << rep.alpha.position() << "\t" << rep.alpha.orientation() << "\t" << rep.alpha.momentum.after() << "\t" << rep.alpha.angular_momentum.after() << "\t" << rep.alpha.momentum.delta() << "\t" << rep.alpha.angular_momentum.delta() << std :: endl;
      }
      else
      {
        oeb << rep.time() << "\t" << rep.beta.position() << "\t" << rep.beta.orientation() << "\t" << rep.beta.momentum.after() << "\t" << rep.beta.angular_momentum.after() << "\t" << rep.beta.momentum.delta() << "\t" << rep.beta.angular_momentum.delta() << std :: endl;
      }
    }
  );

  // Starting the Execution

  my_window.clear();
  my_window.draw(my_engine);
  my_window.flush();
  my_window.wait_click();
  my_window.clear();

  for(double time = 0.; ; time += 0.001)
  {
    my_engine.run(time);
    my_window.clear();
    my_window.draw(my_engine);

    // Time-based Data Gathering

    my_engine.each <molecule>
    (
      complex,
      [&](const molecule & cur)
      {
        // Time - Id - Position - Orientation - Velocity - Angular Velocity
        otb << time << "\t" << cur.tag.id() << "\t" << cur.position() << "\t" << cur.orientation() << "\t" << cur.velocity() << "\t" << cur.angular_velocity() << std :: endl;
      }
    );

    my_window.flush();
  }
}

#endif
