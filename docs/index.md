| **Author**   | **Project** | **Documentation**                                                                   | **Build Status**              |
|:------------:|:-----------:|:-----------------------------------------------------------------------------------:|:-----------------------------:|
|   [**M. Monti**](https://github.com/matteomonti)   |  **nocs**  | [![docs](https://img.shields.io/readthedocs/:packageName/:version.svg?style=plastic)](https://github.com/matteomonti/nocs/blob/master/docs/README.md) | **Linux / MacOS** : [![travis](https://travis-ci.com/Nico-Curti/nocs.svg?branch=master)](https://travis-ci.com/Nico-Curti/nocs) |

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/matteomonti/nocs.svg?style=plastic)](https://github.com/matteomonti/nocs/pulls)
[![GitHub issues](https://img.shields.io/github/issues/matteomonti/nocs.svg?style=plastic)](https://github.com/matteomonti/nocs/issues)

[![GitHub stars](https://img.shields.io/github/stars/matteomonti/nocs.svg?label=Stars&style=social)](https://github.com/matteomonti/nocs/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/matteomonti/nocs.svg?label=Watch&style=social)](https://github.com/matteomonti/nocs/watchers)

# NOCS
### (Not Only Colliding Spheres)

Exact 2D gas dynamics framework.
For documentation, visit [here](https://github.com/matteomonti/nocs/blob/master/docs/README.md).

# Getting started with nocs

## Basic commands

### Libraries to be included

```cpp
#include "engine/engine.hpp"  /* This library contains the main core of the
                                 simulation and all the components necessary */

#include "graphics/window.h"  /* This library contains the tools for creating
                                 graphical representations of the simulation
                                 and it's therefore optional for the actual
                                 execution of a simulation */
```
### Declaring the fundamental thing

```cpp
int main()
{
  engine my_engine(6); /* This declares an engine with a 6x6 grid subdivision.
                          my_engine will then be the framework for the entire
                          simulation */
}
```

#### How to deal with the grid

The engine's space is square of unit size.
Since it would be not ideal to compute the possible collision between two molecules far far away (there could be something like 10'000 more molecules between them), it is good to split out the space into smaller region, in order to analyze only the possible future interaction between molecules in the same zone or in adjacent zones.
Therefore, if you have elements that are at least smaller than a circle of diameter 0.1, you can set a proper grid that will speed up the computational time. (in this case the fineness limit of the grid is `1 / (0.1 * 2) = 5`)

### Building your first molecules and giving them a nice tag

```c++
int main()
{
  engine my_engine(6); // 6x6 zones engine

  enum tags {heavy, light}; // creating some handy arbitrary tags for any possible need

  /*Creating a handful of molecules*/

  for(double x = 0.1; x <= 0.9; x += 0.1)
      for(double y = 0.1; y <= 0.4; y += 0.1)
      {
          molecule my_molecule
          (
              { // Array of atoms
                  // First atom
                  {
                    {0., 0.}, // Position (arbitrary reference system)
                    1.,       // Mass
                    0.005     // Radius
                  },
                  // Second atom
                  {{0., 0.02}, 10., 0.015}
              },
              {x, y},   // Position of center of mass
              {0, 0},   // Velocity of center of mass
              0.,       // Initial orientation (in radians)
              M_PI / 4. // Angular velocity (in radians / time unit)
          );

          size_t my_molecule_id = my_engine.add(my_molecule);
          // Now the molecule is in the engine, ready to work.
          // The function returns the id of the molecule inside the engine.

          my_engine.tag(my_molecule_id, heavy);
          // Adds tag heavy to the molecule.
          // REMARK: you can add tags to molecules only
          //  after inserting them into the engine.
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

              swap *= -1; // Serves the purpose to have a null total momentum

              size_t my_other_molecule_id = my_engine.add(my_other_molecule);
              my_engine.tag(my_other_molecule_id, light);
          }
}
```

### Bulding a bumper and placing it inside the engine

```cpp
int main()
{
  //[...]

  bumper my_bumper(
    {0.5, 0.5}, // Position
    0.03        // Radius
  );

  my_engine.add(my_bumper);
}
```

### Changing the elasticity of the collision between two molecules

```cpp
int main()
{
  //[...]

  my_engine.elasticity(heavy, heavy, 0.8); // Now if two molecules with tag
    // heavy collide, the collision will be anelastic with a coefficent of 0.8

  my_engine.elasticity(light, 1.5); // Now any collision involving a molecule
    // with tag light will be superelastic with a coefficent of 1.5

  my_engine.elasticity(1.0); // Now every collision is just normal
                             // and fully elastic
}
```

### Executing the simulation

```cpp
int main()
{
  //[...]

  for(double time = 0.; ; time += 0.01)
    my_engine.run(time); // Run UNTIL time...

}
```
**REMARK: remember that this simulation is event-based, therefore you have to specify at what times you want to gather pictures of the simulation space. But remember then that a smaller delta time implies more integrations, which implies more numerical errors.**

### Subscribing to an event

If you want to gather only the data about a particular kind of event involving only a particular kind of molecules, you can use this subscription system to build lambda functions that will set off only when the molecules with the given tags are involved in an event.

```cpp
//#[...]
#include <iostream>

int main()
{
  //[...]

  size_t id_of_subscription;

  id_of_subscription = my_engine.on // I want to subscribe to...
    <events :: molecule>  // ...any collision between two molecules
    ( // So I make a lambda function that takes this kind of report as argument
      [&](const report <events :: molecule> my_report)
      {
        /*and I write now here what I want it to do and print*/

        std :: cout << "There has been a collision between "
          << my_report.alpha.id() << " and "
          << my_report.beta.id() << std :: endl;

        std :: cout << "Delta energy for alpha: "
          << my_report.alpha.energy.delta() << std :: endl;
      }
    ); // and I've also memorized the subscription's id

  my_engine.on // I want to subscribe to...
    <events :: bumper>  // ...any collision between a bumper and a molecule...
    (
      heavy,  // ...that involves a molecule with a tag heavy

      // So I make a lambda function that takes this kind of report as argument
      [&](const report <events :: bumper> my_report)
      {
        /*and I write now here what I want it to do and print*/

        std :: cout << "There has been a collision between "
          << my_report.id() << " and " << a bumper << std :: endl;

        std :: cout << "And the molecule was heavy!" << std :: endl;
      }
    );

  my_engine.on // I want to subscribe to...
    <events :: molecule>  // ...any collision between a molecule and a molecule
    (
      heavy,  // ...that involves a molecule with a tag heavy
      light,  // ...AND a molecule with a tag light
      // So I make a lambda function that takes this kind of report as argument
      [&](const report <events :: molecule> my_report)
      {
        /*and I write now here what I want it to do and print*/

        std :: cout << "There has been a VERY SPECIFIC collision between "
          << my_report.alpha.id() << " and "
          << my_report.beta.id() << std :: endl;

        std :: cout << "Delta energy for alpha: "
          << my_report.alpha.energy.delta() << std :: endl;
      }
    );

  //...time goes on...

  my_engine.unsubscribe(id_of_subscription) // Now I want to unsubscribe from
                      // the first subscription because I don't need it anymore
}
```

### Gathering informations about specific groups of molecules

```cpp
int main()
{
  //[...]

  double total_energy = 0.;

  my_engine.each <molecule>
  (
    [&](const molecule & current_molecule)
  /* Dear engine, for each molecule, please execute this lambda
     that accepts a const reference to the current molecule and captures
     total_energy.
     Each time it is called the lambda adds to total_energy the energy
     of the current molecule.
     Also known as: sum the energies of all the molecules */
    {
        total_energy += current_molecule.energy();
    }
  );

  double total_heavy_energy = 0.;

  my_engine.each <molecule>
  (
    heavy,
    [&](const molecule & current_molecule)
  /* Dear engine, for each molecule with tag fatty, please execute this lambda
     that accepts a const reference to the current molecule and captures
     fatty_total_energy.
     Each time it is called the lambda adds to total_heavy_energy the energy
     of the current molecule.
     Also known as: sum the energies of all the heavy molecules */
    {
        total_heavy_energy += current_molecule.energy();
    }
  );
}
```

### Resetting the energy of one or more molecules

If you want to alter the energy of a molecule and at the same time maintaining all the proportion in the energy distribution (translational and rotational) you can use these methods:

```cpp
int main()
{
  //[...]

  my_engine.reset.energy.id(1, 10.5)
  // set the energy of the molecule with id 1 to 10.5 units of energy

  my_engine.reset.energy.tag(heavy, 0.1)
  // set the energy of all the molecules with tag heavy to 0.1 units of energy

  my_engine.reset.energy.all(1.0)
  // Now every molecule has 1 unit of energy as energy
}
```
### And now, some grpahics

```cpp

int main()
{
  engine my_engine(6);

  //[... adding random things into the engine just like above]

  molecule * a_random_molecule = new molecule (/*stuff*/);
  bumper * a_random_bumper = new bumper(/*stuff*/);

  my_engine.add(a_random_molecule);
  my_engine.add(a_random_bumper);

  window my_window;
  // Initialize a window with standard parameters (which is highly suggested)

  my_window.wait_click();
  // Blocks the execution until a mouse click is detected inside the window

  my_window.wait_enter();
  // Blocks the execution until an enter click
  // is detected with the cursor inside the window

  my_window.draw(my_engine);
  // I want you window to draw all the elements inside engine

  my_window.flush();
  // And now render what I have just said

  my_window.wait_click();

  my_window.clear();
  // And now clean everything! (you may want to use a wait_click() or a usleep()
  // in order to actually see something)

  my_window.draw(my_engine, heavy);
  // Now I want you window to draw all the elements inside engine with tag heavy

  my_window.draw(* a_random_molecule); // Draw that molecule!
  my_window.draw(* a_random_bumper); // Draw that bumper!

  my_window.flush(); // Now render everything!
  my_window.wait_click();
}

```
