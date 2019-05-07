## Class `window`

### Overview
Class `window` is a simple graphical interface based on `GLUT` which allows the user to visualize an `engine` in a specific window.

The class executes the entire window instance into a separate thread, so that the requested drawing procedures do not interfere with the actual calculations.

Moreover, it offers the method `wait_click` for pausing the entire program until a mouse click is detected inside the window.

The entire class is wrapped into the `namespace graphics`, so that its helper structs do not interfere with the rest of the code.

### Interface

#### Constructor

`window()`

Starts a `GLUT` window in a separate thread.

**REMARK: you can only start one window at the time.**

#### Public methods

  * `static void draw(const engine & engine)`

    draws all the elements of the simulation.

  * `static void draw(const engine & engine, const unit8_t & tag)`

    draws the elements of the simulation with the given tag.

  * `static void wait_click()`

    blocks the execution until a mouse click is detected inside the window.
