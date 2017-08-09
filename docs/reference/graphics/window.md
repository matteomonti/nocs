## Class `window`

### Overview
Class `window` is a wrapper for class `lockpick`, which is indeed a wrapper for the graphic library `passe_par_tout` (http://www.physycom.unibo.it/labinfo/passe_par_tout.php) and inherits from class `lockpick :: window`.
The wrapping allows the user to easly observe the whole simulation or, with the tag system, just part of the elements of the simulation.

### Interface

#### Constructor

`window(const char * name_of_the_window = nullptr, int width = __default_width, int height = __default_height, int x_position = 0, int y_position = 0, lockpick :: color background = lockpick :: color(255, 255, 255), int frame_width_percentage = 95, int frame_height_percentage = 95)`
builds a window with the given name and the given parameters.

Example of usage: `window my_window("my_pretty_window");`

**REMARK: beside of the window's name, default parameters are ideal for a correct visualization of the simulation.**

#### Public methods

  * `void draw(const engine & engine)`
    draws all the elements of the simulation **at their current time**.

  * `void draw(const engine & engine, const unit8_t & tag)`
    draws all the elements of the simulation with the given tag **at their current time**.

  * `void draw(const molecule & molecule)`
    draws the given molecule **at its current time**.

  * `void draw(const bumper & bumper)`
    draws the given bumper **at its current time**.

**REMARK: All these methods require the** `void flush()` **method at the end (see below).**

#### Fundamental inherited public methods

**REMARK: these methods come from src/graphics/lockpick.h but they are reported here for convenience.**

  * `static void wait_enter()`
    blocks the execution until an enter click is detected with the cursor inside the window.

  * `static void wait_click()`
    blocks the execution until a mouse click is detected inside the window.

  * `void flush()`
    after the listing of all the things to draw with the `draw(...)` methods, this command executes the actual rendering.

  * `void clear()`
    clear the window from all the previous drawings.
