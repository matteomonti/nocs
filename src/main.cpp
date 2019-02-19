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

const unsigned int N_LIGHT_MOLECULES = 1000;
const unsigned int N_TRACED_LIGHT_MOLECULES = 1;
const double LIGHT_MOLECULE_RADIUS = 0.004;
const double LIGHT_MOLECULE_MASS = 1.0;
const double LIGHT_MOLECULE_STARTING_ENERGY = 0.05;

const unsigned int N_HEAVY_MOLECULES = 1000;
const unsigned int N_TRACED_HEAVY_MOLECULES = 1;
const double HEAVY_MOLECULE_RADIUS = 0.006;
const double HEAVY_MOLECULE_MASS = 100.0;
const double HEAVY_MOLECULE_STARTING_ENERGY = 0.05;

const double TIME_TRACING_SKIP = 0.001; // visto che le molecole partono tutte pigiate come acciughe... magari val la pena di saltare il tracciamento degli eventi pigiati "al tempo 0"? Non lo so... val la pena di testare.

const double SIMULATION_TIME = 100.0; // Tempo di arrivo finale della simulazione
const unsigned int N_SAMPLES = 1000; // Quanti samples intermedi far fare alla simulazione? (questi verranno distribuiti uniformemente lungo l'esecuzione)

int main()
{
    // Output setup
    ofstream out_all ("output_all.txt");
    ofstream out_traced ("output_traced.txt");

    window my_window; // Per la grafica...
    engine my_engine(50); // Regolare in base a dimensioni scelte

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

    // Creazione dei tag
    enum tags {light, heavy, traced};
    
    double lower_bound = 0;
    double upper_bound = M_PI * 2;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    re.seed(42); // PSEUDORANDOM SEED (credo si faccia così?)

    // Aggiunta delle molecole leggere

    double starting_velocity = pow(LIGHT_MOLECULE_STARTING_ENERGY / (0.5 * LIGHT_MOLECULE_MASS), 0.5);

    unsigned int inserted = 0;

    for (double y = LIGHT_MOLECULE_RADIUS; y < 1.0 - LIGHT_MOLECULE_RADIUS; y += 2 * LIGHT_MOLECULE_RADIUS)
    {
        for (double x = 2 * (LIGHT_MOLECULE_RADIUS + bumper_radius); x < 1.0 - 2 * (LIGHT_MOLECULE_RADIUS + bumper_radius); x += 2 * LIGHT_MOLECULE_RADIUS)
        {
            double angle = unif(re);
            double v_x = starting_velocity * cos(angle);
            double v_y = starting_velocity * sin(angle);
            molecule my_molecule(
                {{{0., 0.}, LIGHT_MOLECULE_MASS, LIGHT_MOLECULE_RADIUS}},
                {x, y},
                {v_x, v_y},
                0.,
                0.);
            size_t my_id = my_engine.add(my_molecule);
            my_engine.tag(my_id, light);
            if (inserted < N_TRACED_LIGHT_MOLECULES)
                my_engine.tag(my_id, traced);
            inserted++;
            if (inserted >= N_LIGHT_MOLECULES)
                break;
        }
        if (inserted >= N_LIGHT_MOLECULES)
            break;
    }

    // Aggiunta delle molecole pesanti (occhio che non si intersechino!)

    starting_velocity = pow(HEAVY_MOLECULE_STARTING_ENERGY / (0.5 * HEAVY_MOLECULE_MASS), 0.5);

    inserted = 0;

    for (double y = 1.0 - HEAVY_MOLECULE_RADIUS; y > HEAVY_MOLECULE_RADIUS; y -= 2 * HEAVY_MOLECULE_RADIUS)
    {
        for (double x = 2 * (HEAVY_MOLECULE_RADIUS + bumper_radius); x < 1.0 - 2 * (HEAVY_MOLECULE_RADIUS + bumper_radius); x += 2 * HEAVY_MOLECULE_RADIUS)
        {
            double angle = unif(re);
            double v_x = starting_velocity * cos(angle);
            double v_y = starting_velocity * sin(angle);
            molecule my_molecule(
                {{{0., 0.}, HEAVY_MOLECULE_MASS, HEAVY_MOLECULE_RADIUS}},
                {x, y},
                {v_x, v_y},
                0.,
                0.);
            size_t my_id = my_engine.add(my_molecule);
            my_engine.tag(my_id, light);
            if (inserted < N_TRACED_HEAVY_MOLECULES)
                my_engine.tag(my_id, traced);
            inserted++;
            if (inserted >= N_HEAVY_MOLECULES)
                break;
        }
        if (inserted >= N_HEAVY_MOLECULES)
            break;
    }

    // Sottoscrizione agli eventi delle molecole sotto tracciamento

    my_engine.on <events :: molecule>
    (
        traced,
        [&](const report <events :: molecule> my_report)
        {   
            if(my_report.time() >= TIME_TRACING_SKIP)
            {
                out_traced << std ::fixed << std ::setprecision(8) << my_report.time() << "\t"
                           << std ::fixed << my_report.alpha.id() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.mass() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.energy.after() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.position().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.position().y << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.velocity.after().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.alpha.velocity.after().y << std::endl;

                out_traced << std ::fixed << std ::setprecision(8) << my_report.time() << "\t"
                           << std ::fixed << my_report.beta.id() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.mass() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.energy.after() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.position().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.position().y << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.velocity.after().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.beta.velocity.after().y << std::endl;
            } 
        }
    );

    my_engine.on <events :: bumper>
    (
        traced,
        [&](const report <events :: bumper> my_report)
        {
            if(my_report.time() >= TIME_TRACING_SKIP)
            {
                out_traced << std ::fixed << std ::setprecision(8) << my_report.time() << "\t"
                           << std ::fixed << my_report.id() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.mass() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.energy.after() << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.position().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.position().y << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.velocity.after().x << "\t"
                           << std ::fixed << std::setprecision(8) << my_report.velocity.after().y << std::endl;
            }
        }
    );

    // Resto delle cose brutte

    my_engine.each<molecule>([&](const molecule &current_molecule) {
        out_all << std ::fixed << std ::setprecision(2) << 0.0 << "\t"
            << std ::fixed << current_molecule.mass() << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.energy() << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.position().x << "\t"
            << std ::fixed << std ::setprecision(8) << current_molecule.position().y << std::endl;
    });

    my_window.draw(my_engine); // Draw the content of the engine on the window
    my_window.flush();         // You need this to render on screen, draw is not sufficient
    my_window.wait_click();    // Guess what
#ifdef __graphics__
    std :: cout << "Simulation Start!!!" << std :: endl;
#endif

    double time_interval = SIMULATION_TIME / N_SAMPLES;

    for(unsigned int i = 1; i <= N_SAMPLES; ++i)
    {
        my_engine.run(i * time_interval); // Run UNTIL time
        
        // Report di ogni molecola sul file di testo...
        my_engine.each<molecule>([&](const molecule &current_molecule) {
            out_all << std ::fixed << std ::setprecision(2) << i * time_interval << "\t"
                << current_molecule.mass() << "\t"
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
