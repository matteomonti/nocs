#include "molecule_molecule.h"

namespace events
{
  // Constructors

  molecule_molecule :: molecule_molecule(molecule & alpha, molecule & beta)
  {
    vec xa = alpha.position();
    vec xb = beta.position();

    vec va = alpha.velocity();
    vec vb = beta.velocity();

    if(alpha.time() > beta.time())
      xb += vb * (alpha.time() - beta.time());
    else
      xa += va * (beta.time() - alpha.time());

    double time = std :: max(alpha.time(), beta.time());

    // Test 1: molecules approaching

    double b = 2. * (xa - xb) * (va - vb);

    if(b >= 0)
    {
      this->_happens = false;
      return;
    }

    // Test 2: collision range

    double a = ~(va - vb);
    double c = ~(xa - xb) - (alpha.radius() + beta.radius()) * (alpha.radius() + beta.radius());

    double beg = newton :: quadratic(a, b, c, time);

    if(isnan(beg))
    {
      this->_happens = false;
      return;
    }

    // Determine end of collision range

    double mid = time + sqrt(~(xa - xb) / ~(va - vb)); // Maximum proximity of molecules centers of mass
    double end = 2. * mid - beg; // Parabolas are symmetric

    std :: cout << "beg: " << beg << std :: endl;
    std :: cout << "end: " << end << std :: endl;
  }

  // Methods

  bool molecule_molecule :: current()
  {
    return this->_alpha.version == this->_alpha.molecule->version() && this->_beta.version == this->_beta.molecule->version();
  }

  void molecule_molecule :: resolve()
  {
  }
};
