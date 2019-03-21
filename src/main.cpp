#ifdef __main__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>


#include "engine/engine.hpp"
#include "graphics/window.h"
#include "tqdm/tqdm.h"

// Parametri:

const bool LOAD_FROM_FILES = false; // Si vuole caricare una vecchia configurazione già termalizzata? 

const bool WALLS = true; // Ci sono o no le pareti di bumpers calde e fredde?
const bool MAXWELL = false; // distribuiamo secondo maxwelliana le temperature dei bumpers?
const double ALPHA = 1.0; // il parametro beta della funzione gamma della maxwelliana viene ricavato dal fatto che la media è E(X) = alpha/beta

const unsigned int N_BUMPERS = 100; // Più bumpers significa parete più fina e "liscia", visto che sono comunque sfere
const double COLD_TEMPERATURE = 0.01;
const double HOT_TEMPERATURE = 0.1;

const unsigned int N_LIGHT_MOLECULES = 1000;
const unsigned int N_TRACED_LIGHT_MOLECULES = 1;
const double LIGHT_MOLECULE_RADIUS = 0.004;
const double LIGHT_MOLECULE_SPACING = 0.0005;
const double LIGHT_MOLECULE_MASS = 1.0;
const double LIGHT_MOLECULE_STARTING_ENERGY = 0.05;

const unsigned int N_HEAVY_MOLECULES = 0;
const unsigned int N_TRACED_HEAVY_MOLECULES = 1;
const double HEAVY_MOLECULE_RADIUS = 0.006;
const double HEAVY_MOLECULE_SPACING = 0.0005;
const double HEAVY_MOLECULE_MASS = 100.0;
const double HEAVY_MOLECULE_STARTING_ENERGY = 0.05;

const double TIME_TRACING_SKIP = 0.001; // visto che le molecole partono tutte pigiate come acciughe... magari val la pena di saltare il tracciamento degli eventi pigiati "al tempo 0"? Non lo so... val la pena di testare.

const double SIMULATION_TIME = 10.0; // Tempo di arrivo finale della simulazione
const unsigned int N_SAMPLES = 100; // Quanti samples intermedi far fare alla simulazione? (questi verranno distribuiti uniformemente lungo l'esecuzione)

int main()
{
    // RANDOM ENGINE SETUP
    std::default_random_engine re;
    // PSEUDORANDOM SEED (credo si faccia così?)
    re.seed(42);

    // Output setup
    std :: ofstream out_all ("output_all.txt");
    std :: ofstream out_traced ("output_traced.txt");

    // Input setup (se necessario)
    std :: ifstream in_light;
    std :: ifstream in_heavy;
    double x_file, y_file;
    if (LOAD_FROM_FILES)
    {
        in_light = std ::ifstream("input_light.txt");
        in_heavy = std ::ifstream("input_heavy.txt");            
    }

    window my_window; // Per la grafica...
    engine my_engine(50); // Regolare in base a dimensioni scelte

    // Raggio dei bumpers?
    double bumper_radius = 1. / (N_BUMPERS * 2);

    // Costruzione delle pareti
    if (WALLS)
    {
        // Se si usa maxwelliana servono
        const double BETA_COLD = ALPHA / COLD_TEMPERATURE;
        const double BETA_HOT = ALPHA / HOT_TEMPERATURE;
        std::gamma_distribution<double> gamma_cold(ALPHA, BETA_COLD);
        std::gamma_distribution<double> gamma_hot(ALPHA, BETA_HOT);

        for (int x = 0; x < N_BUMPERS; ++x)
        {
            bumper cold_bumper(
                {bumper_radius, x * bumper_radius * 2}, // coordinate
                bumper_radius,                     // raggio
                (MAXWELL ? gamma_cold(re) : COLD_TEMPERATURE)                   // temperatura fredda
            );
            bumper hot_bumper(
                {1.0 - bumper_radius, x * bumper_radius * 2}, // coordinate
                bumper_radius,                            // raggio
                (MAXWELL ? gamma_hot(re) : HOT_TEMPERATURE)                           // temperatura calda
            );
            my_engine.add(cold_bumper);
            my_engine.add(hot_bumper);
        }
    }

    // Creazione dei tag
    enum tags {light, heavy, traced};
    // Vector per gli ID tracciati
    std :: vector <size_t> ids;
    
    double lower_bound = 0;
    double upper_bound = M_PI * 2;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    
    // Aggiunta delle molecole leggere

    double starting_velocity = pow(LIGHT_MOLECULE_STARTING_ENERGY / (0.5 * LIGHT_MOLECULE_MASS), 0.5);

    unsigned int inserted = 0;
    if (N_LIGHT_MOLECULES)
        for (double y = LIGHT_MOLECULE_RADIUS; y < 1.0 - LIGHT_MOLECULE_RADIUS; y += 2 * LIGHT_MOLECULE_RADIUS + LIGHT_MOLECULE_SPACING)
        {
            for (double x = 2 * (LIGHT_MOLECULE_RADIUS + bumper_radius); x < 1.0 - 2 * (LIGHT_MOLECULE_RADIUS + bumper_radius); x += 2 * LIGHT_MOLECULE_RADIUS + LIGHT_MOLECULE_SPACING)
            {
                double angle = unif(re);
                double v_x = starting_velocity * cos(angle);
                double v_y = starting_velocity * sin(angle);
                molecule my_molecule;
                if (LOAD_FROM_FILES)
                {
                    in_light >> x_file >> y_file;
                    in_light >> v_x >> v_y;
                    my_molecule = molecule(
                        {{{0., 0.}, LIGHT_MOLECULE_MASS, LIGHT_MOLECULE_RADIUS}},
                        {x_file, y_file},
                        {v_x, v_y},
                        0.,
                        0.);
                }
                else
                {
                    my_molecule = molecule(
                        {{{0., 0.}, LIGHT_MOLECULE_MASS, LIGHT_MOLECULE_RADIUS}},
                        {x, y},
                        {v_x, v_y},
                        0.,
                        0.);
                }
                size_t my_id = my_engine.add(my_molecule);
                my_engine.tag(my_id, light);
                if (inserted < N_TRACED_LIGHT_MOLECULES)
                {
                    my_engine.tag(my_id, traced);
                    ids.push_back(my_id);
                }
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
    if (N_HEAVY_MOLECULES)
        for (double y = 1.0 - HEAVY_MOLECULE_RADIUS; y > HEAVY_MOLECULE_RADIUS; y -= 2 * HEAVY_MOLECULE_RADIUS + HEAVY_MOLECULE_SPACING)
        {
            for (double x = 2 * (HEAVY_MOLECULE_RADIUS + bumper_radius); x < 1.0 - 2 * (HEAVY_MOLECULE_RADIUS + bumper_radius); x += 2 * HEAVY_MOLECULE_RADIUS + HEAVY_MOLECULE_SPACING)
            {
                double angle = unif(re);
                double v_x = starting_velocity * cos(angle);
                double v_y = starting_velocity * sin(angle);
                molecule my_molecule;
                if (LOAD_FROM_FILES)
                {
                    in_heavy >> x_file >> y_file;
                    in_heavy >> v_x >> v_y;
                    my_molecule = molecule(
                        {{{0., 0.}, HEAVY_MOLECULE_MASS, HEAVY_MOLECULE_RADIUS}},
                        {x_file, y_file},
                        {v_x, v_y},
                        0.,
                        0.);
                }
                else
                {
                    my_molecule = molecule(
                        {{{0., 0.}, HEAVY_MOLECULE_MASS, HEAVY_MOLECULE_RADIUS}},
                        {x, y},
                        {v_x, v_y},
                        0.,
                        0.);
                }
                size_t my_id = my_engine.add(my_molecule);
                my_engine.tag(my_id, light);
                if (inserted < N_TRACED_HEAVY_MOLECULES)
                {
                    my_engine.tag(my_id, traced);
                    ids.push_back(my_id);
                }
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
                if (std :: find(ids.begin(), ids.end(), my_report.alpha.id()) != ids.end())
                    out_traced << std ::fixed << std ::setprecision(8) << my_report.time() << "\t"
                               << std ::fixed << my_report.alpha.id() << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.mass() << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.energy.after() << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.position().x << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.position().y << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.velocity.after().x << "\t"
                               << std ::fixed << std::setprecision(8) << my_report.alpha.velocity.after().y << std::endl;
                else
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

    my_window.draw(my_engine); // Draw the content of the engine on the window
    my_window.flush();         // You need this to render on screen, draw is not sufficient
    my_window.wait_click();    // Guess what
#ifdef __graphics__
    std :: cout << "Simulation Start!!!" << std :: endl;
#endif

    double time_interval = SIMULATION_TIME / N_SAMPLES;
    
    // ORA TQDM È ANCHE IN C++!!!
    tqdm bar;
    // Il mio terminale windows non supporta molti caratteri ed è brutto a vedersi...
    bar.set_theme_basic();
    // Se non vuoi i colori attiva questa riga...
    //bar.disable_colors();
    
    for(unsigned int i = 0; i <= N_SAMPLES; ++i)
    {
        bar.progress(i, N_SAMPLES);
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
        usleep(10.e4);
    #endif
    }
}

#endif
