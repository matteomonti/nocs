#ifdef __main__

#include "experiments/experiment.h"

int main()
{
  // Setup File Stream

  std :: ofstream oeb("/home/carlidel/Scrivania/output_event_based.txt");

  std :: ofstream otb("/home/carlidel/Scrivania/output_time_based.txt");

  // Setup Random Generator

  double lower_bound = -1;
  double upper_bound = 1;

  std :: uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std :: default_random_engine re;

  experiment :: brownian(oeb, otb, unif, re);
}

#endif
