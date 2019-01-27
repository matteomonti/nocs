#ifdef __main__

#include <iostream>
#include <iomanip>

#include "engine/engine.hpp"
#include "graphics/window.h"

int main()
{
    enum tags {fatty, ninja};

    window my_window; // Just a window

    engine my_engine(3); // 6x6 zones

    molecule my_molecule
    (
        {{{0., 0.}, 1., 0.005}},
        {0.5, 0.5},
        {0.2, 0.0},
        0.,
        0.
    );
    size_t my_molecule_id = my_engine.add(my_molecule);

    bumper cold_bumper({0.05, 0.5}, 0.05, 0.01);
    bumper hot_bumper({0.95, 0.5}, 0.05, 0.5);
    my_engine.add(cold_bumper);
    my_engine.add(hot_bumper);

    my_window.draw(my_engine); // Drasw the content of the engine on the window
    my_window.flush();         // You need this to render on screen, draw is not sufficient
    my_window.wait_click();    // Guess what

    for(double time = 0.;; time += 0.01)
    {
        my_engine.run(time); // Run UNTIL time
        my_window.clear();   // Remove what was drawn before
        my_window.draw(my_engine);
        my_window.flush();

        usleep(1.e4);
    }
}

#endif
