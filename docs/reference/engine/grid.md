## Class `grid` (engine/grid.h)

### Overview

Class `grid` implements a subdivision of the simulation zone into smaller regions. This allows to reduce the volume of many analyisis and computations, since each element of the simulation needs now to be compared only with other elements in the same region or in a neighboring region.

### Public nested classes

#### `class mark`

this class is friend with `grid` and, when included into an object of the simulation (like `molecule`), it's used to keep track of the position of that object inside the grid.

**Getters**

  * `size_t x() const`
    returns the x coordinate of the analyzed object inside the grid.

  * `size_t y() const`
    returns the y coordinate of the analyzed object inside the grid.

### Interface

#### Constructor

  * `grid(const size_t & fineness)`
    builds a grid of the given fineness. (e.g. a fineness of 2 implies a grid of 2x2 regions)

#### Destructor

  * `~grid()`
    destroys the grid.

#### Getters

  * `const size_t & fineness() const;`
    returns the fineness of the grid.

#### Methods

  * `void add(molecule & molecule)`
    adds the given molecule into the grid.

  * `void add(bumper & bumper)`
    adds the given bumper into the grid.

  * `void remove(molecule & molecule)`
    removes the given molecule from the grid.

  * `void update(molecule & molecule, const vec :: fold & fold)`
    updates the collocation of the molecule inside the grid, .

  * `template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type * = nullptr> void each(const size_t & x_coordinate, const size_t & y_coordinate, const lambda & function)`
    given the coordinates of a region and a lambda function that takes as argument a molecule, executes that function to each molecule inside the chosen region.

  * `template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, bumper> :: value> :: type * = nullptr> void each(const size_t & x_coordinate, const size_t & y_coordinate, const lambda & function)`
    given the coordinates of a region and a lambda function that takes as argument a bumper, executes that function to each bumper inside the chosen region.
