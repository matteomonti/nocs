#include "molecule_molecule.hpp"

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

    for(double t = beg; t < end; t += (end - beg) / 2000.)
    {
      double distance = ~(position(alpha, 0, t) - position(beta, 0, t));
      // std :: cout << t << "\t" << distance << std :: endl;
    }
    double step = 0.5 * std :: min(std :: min(M_PI / fabs(alpha.angular_velocity() + beta.angular_velocity()), M_PI / fabs(alpha.angular_velocity() - beta.angular_velocity())), std :: min(M_PI / fabs(2. * alpha.angular_velocity()), M_PI / fabs(2. * beta.angular_velocity())));
    // TODO: Find out better euristics for maximum cropping of minima and maxima?


  }

  // Methods

  bool molecule_molecule :: current()
  {
    return this->_alpha.version == this->_alpha.molecule->version() && this->_beta.version == this->_beta.molecule->version();
  }

  void molecule_molecule :: resolve()
  {
  }

  // Private methods

  double molecule_molecule :: collision(const molecule & alpha, const size_t & index_alpha, const molecule & beta, const size_t & index_beta, const double & beg, const double & end, const double & step)
  {
    double rbeg = NaN;
    double rend = NaN;

    for(double binbeg = beg; binbeg < end; binbeg += step)
    {
      double binend = std :: min(end, binbeg + step);
      
      auto distsquared = [&](const double & time)
      {
        return ~(position(alpha, index_alpha, time) - position(beta, index_beta, time));
      };
      
      double binmin = gss :: min(distsquared, binbeg, binend);
      
      if(distsquared(binmin) > 0)
        continue;
      
      double binmax = gss :: max(distsquared, binbeg, binend);
    }

    return 0;
  }
};
