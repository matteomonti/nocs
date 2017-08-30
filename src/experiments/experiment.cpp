#include "experiment.h"

namespace experiment
{
  void brownian(std :: ofstream & oeb, std :: ofstream & otb, std :: uniform_real_distribution<double> & unif, std :: default_random_engine & re)
  {
    // Headlines

    oeb << "Time \t Position \t Orientation \t Momentum \t Angluar Momentum \t Delta Momentum \t Delta Angular Momentum" << std :: endl;
    oeb.precision(6);
    oeb.setf( std::ios::fixed, std:: ios::floatfield );

    otb << "Time \t Id \t Position \t Orientation \t Velocity \t Angular Velocity" << std :: endl;
    otb.precision(6);
    otb.setf( std::ios::fixed, std:: ios::floatfield );


    // Tags

    enum tags {simple, complex};

    // Initialization

    engine my_engine(9);
    window my_window;

    // Wind Breaker!

    bumper wind_breaker({0., 0.}, 0.005);
    my_engine.add(wind_breaker);

    // Simple molecules

    double diameter = 0.01;

    for(double x = 0.015; x < 0.45; x += diameter * 2)
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

    for(double x = 0.45 + diameter / 2; x < 0.55; x += diameter * 2)
      for(double y = 0.015; y <= 0.3; y += diameter * 2)
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

    for(double x = 0.45 + diameter / 2; x < 0.55; x += diameter * 2)
      for(double y = 0.7; y <= 0.995; y += diameter * 2)
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

    for(double x = 0.55 + diameter / 2; x < 0.995; x += diameter * 2)
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
        {0.5, 0.5},
        {0,0},
        M_PI / 2,
        0
    );

    size_t id_complex = my_engine.add(second);
    my_engine.tag(id_complex, complex);

    // Event-Based Data Gathering (works for single molecule)

    my_engine.on <events :: molecule>
    (
      complex,
      [&](const report <events :: molecule> rep)
      {
        // Time - Position - Orientation - Momentum - Angluar Momentum - Delta Momentum - Delta Angular Momentum - orientation Analysis.
        if(rep.alpha.id() == id_complex)
        {
          oeb << rep.time() << "\t" << rep.alpha.position() << "\t" << rep.alpha.orientation() << "\t" << rep.alpha.momentum.after() << "\t" << rep.alpha.angular_momentum.after() << "\t" << rep.alpha.momentum.delta() << "\t" << rep.alpha.angular_momentum.delta() << "\t";
          // Orientation Analysis
          oeb << rep.alpha.momentum.delta() % (-rep.alpha.momentum.orientation()) << std :: endl;
        }
        else
        {
          oeb << rep.time() << "\t" << rep.beta.position() << "\t" << rep.beta.orientation() << "\t" << rep.beta.momentum.after() << "\t" << rep.beta.angular_momentum.after() << "\t" << rep.beta.momentum.delta() << "\t" << rep.beta.angular_momentum.delta() << std :: endl;
          // Orientation Analysis
          oeb << rep.beta.momentum.delta() % (-rep.beta.momentum.orientation()) << std :: endl;
        }
      }
    );

    // Starting the Execution

    my_window.clear();
    my_window.draw_with_grid(my_engine);
    my_window.flush();
    my_window.wait_click();
    my_window.clear();

    for(double time = 0.; ; time += 0.001)
    {
      std :: cout << time << std :: endl;
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


// Disequilibrium


  void disequilibrium(std :: ofstream & oeb, std :: ofstream & otb, std :: uniform_real_distribution<double> & unif, std :: default_random_engine & re)
  {
    // Headlines

    otb << "Time \t Id \t Position \t Orientation \t Velocity \t Angular Velocity" << std :: endl;
    otb.precision(6);
    otb.setf( std::ios::fixed, std:: ios::floatfield );

    // Tags

    enum tags {hot, cold, medium, complex};

    // Initialization

    engine my_engine(25);
    window my_window;

    // The Walls!

    int fineness = 200;

    // The Trump one
    for(int i = 0; i < fineness; i++)
    {
      bumper wally
      (
        {0., i * (1. / fineness) + (1. / (fineness * 2))},
        1. / (fineness * 2)
      );
      my_engine.add(wally);
    }
    // The hot one
    for(int i = 0; i < fineness; i++)
      if(!(i % 4))
      {
        {
          bumper wally
          (
            {0.15, i * (1. / fineness) + (1. / (fineness * 2))},
            1. / (fineness * 2)
          );
          my_engine.add(wally);
        }
      }
    // The cold one
    for(int i = 0; i < fineness; i++)
      if(!(i % 4))
      {
        {
          bumper wally
          (
            {0.85, i * (1. / fineness) + (1. / (fineness * 2))},
            1. / (fineness * 2)
          );
          my_engine.add(wally);
        }
      }

    // Small molecules

    double diameter = 2. / fineness;

    for(double x = 0.15 + diameter; x < 0.85 - diameter; x += diameter * 2)
      for(double y = 0.; y <= 1 - diameter; y += diameter * 2)
      {
        molecule * first = new molecule
        (
          {
            {{0., 0.}, 1., diameter / 2}
          },
          {x, y},
          {unif(re), unif(re)},
          0.,
          0
        );

        size_t molecule_id = my_engine.add(* first);
        my_engine.tag(molecule_id, medium);
      }

    // Hot molecules

    diameter = 5. / fineness;

    for(double x = 0. + diameter; x < 0.15 - diameter; x += diameter * 2)
      for(double y = 0.; y <= 1 - diameter; y += diameter * 2)
      {
        molecule * first = new molecule
        (
          {
            {{0., 0.}, 4., diameter / 2}
          },
          {x, y},
          {unif(re), unif(re)},
          0.,
          0
        );

        size_t molecule_id = my_engine.add(* first);
        my_engine.tag(molecule_id, hot);
      }

    // Cold molecules

    diameter = 5. / fineness;

    for(double x = 0.85 + diameter; x < 1 - diameter; x += diameter * 2)
      for(double y = 0.; y <= 1 - diameter; y += diameter * 2)
      {
        molecule * first = new molecule
        (
          {
            {{0., 0.}, 4., diameter / 2}
          },
          {x, y},
          {unif(re), unif(re)},
          0.,
          0
        );

        size_t molecule_id = my_engine.add(* first);
        my_engine.tag(molecule_id, cold);
      }

      // First Energy Resetting

      my_engine.reset.energy.tag(hot, 500);
      my_engine.reset.energy.tag(cold, 1);
      my_engine.reset.energy.tag(medium, 1);

      // Starting the Execution

      my_window.clear();
      my_window.draw(my_engine);
      my_window.flush();
      my_window.wait_click();
      my_window.clear();

      for(double time = 0.; ; time += 0.005)
      {
        std :: cout << time << std :: endl;
        my_engine.run(time);
        my_window.clear();
        my_window.draw(my_engine);

        // Try in this way...

        my_engine.reset.energy.tag(hot, 500);
        my_engine.reset.energy.tag(cold, 0.1);

        // Time-based Data Gathering

        my_engine.each <molecule>
        (
          medium,
          [&](const molecule & cur)
          {
            // Time - Id - Position - Velocity
            otb << time << "\t" << cur.tag.id() << "\t" << cur.position() << "\t" << cur.velocity() << std :: endl;
          }
        );

        my_window.flush();
      }
    }
};
