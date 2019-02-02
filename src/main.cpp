#ifdef __main__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <random>

#include "engine/engine.hpp"
#include "graphics/window.h"

// Parametri:

const unsigned int N_BUMPERS = 100; // Più bumpers significa parete più fina e "liscia", visto che sono comunque sfere
const double COLD_TEMPERATURE = 0.1;
const double HOT_TEMPERATURE = 0.01;

const unsigned int N_MOLECULES = 1000;
const double MOLECULE_RADIUS = 0.005; // da questi due parametri si può rompere tutto, osservare le cose con la grafica è fondamentale.
const double MOLECULE_MASS = 1.0;
const double MOLECULE_STARTING_ENERGY = 0.05;

const double SIMULATION_TIME = 100.0; // Tempo di arrivo finale della simulazione
const unsigned int N_SAMPLES = 10; // Quanti samples intermedi far fare alla simulazione? (questi verranno distribuiti uniformemente lungo l'esecuzione)

int main()
{
    // Output setup
    ofstream out ("output_file.txt");

    window my_window; // Per la grafica...
    engine my_engine(20); // Regolare in base a dimensioni scelte

    // Raggio dei bumpers?
    double bumper_radius = 1. / (N_BUMPERS * 2);

    // Costruzione delle pareti
    for (int x = 0; x < N_BUMPERS; ++x)
    {
        bumper cold_bumper(
            {bumper_radius, x * bumper_radius * 2}, // coordinate
            bumper_radius,                     // raggio
            COLD_TEMPERATURE                   // temperatura fredda
        );
        bumper hot_bumper(
            {1.0 - bumper_radius, x * bumper_radius * 2}, // coordinate
            bumper_radius,                            // raggio
            HOT_TEMPERATURE                           // temperatura fredda
        );
        my_engine.add(cold_bumper);
        my_engine.add(hot_bumper);
    }

    // Aggiunta delle molecole (ci devono stare tutte!)

    double starting_velocity = pow(MOLECULE_STARTING_ENERGY / (0.5 * MOLECULE_MASS), 0.5);

    double lower_bound = 0;
    double upper_bound = M_PI * 2;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    re.seed(42); // PSEUDORANDOM SEED (credo si faccia così?)

    unsigned int inserted = 0;

    for (double y = MOLECULE_RADIUS; y < 1.0 - MOLECULE_RADIUS; y += 2 * MOLECULE_RADIUS)
    {
        for (double x = 2 * (MOLECULE_RADIUS + bumper_radius); x < 1.0 - 2 * (MOLECULE_RADIUS + bumper_radius); x += 2 * MOLECULE_RADIUS)
        {
            double angle = unif(re);
            double v_x = starting_velocity * cos(angle);
            double v_y = starting_velocity * sin(angle);
            molecule my_molecule(
                {{{0., 0.}, MOLECULE_MASS, MOLECULE_RADIUS}},
                {x, y},
                {v_x, v_y},
                0.,
                0.);
            my_engine.add(my_molecule);
            inserted++;
            if(inserted >= N_MOLECULES)
                break;
        }
        if (inserted >= N_MOLECULES)
            break;
    }

    my_engine.each<molecule>([&](const molecule &current_molecule) {
        out << std ::fixed << std ::setprecision(2) << 0.0 << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.energy() << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.position().x << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.position().y << std::endl;
    });

    my_window.draw(my_engine); // Draw the content of the engine on the window
    my_window.flush();         // You need this to render on screen, draw is not sufficient
    my_window.wait_click();    // Guess what

    double time_interval = SIMULATION_TIME / N_SAMPLES;

    for(unsigned int i = 1; i <= N_SAMPLES; ++i)
    {
        my_engine.run(i * time_interval); // Run UNTIL time
        
        // Report di ogni molecola sul file di testo...
        my_engine.each<molecule>([&](const molecule &current_molecule) {
            out << std ::fixed << std ::setprecision(2) << i * time_interval << "\t"
                << std ::fixed << std ::setprecision(8) << current_molecule.energy() << "\t"
                << std ::fixed << std ::setprecision(8) << current_molecule.position().x << "\t"
                << std ::fixed << std ::setprecision(8) << current_molecule.position().y << std::endl;
        });

        // Graphics
        my_window.clear();   // Remove what was drawn before
        my_window.draw(my_engine);
        my_window.flush();
    #ifdef __graphics__
        usleep(5.e4);
    #endif
    }
}

#endif
