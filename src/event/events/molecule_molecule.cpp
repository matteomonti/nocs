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

    double radiisquared = (alpha.radius() + beta.radius()) * (alpha.radius() + beta.radius());

    if(alpha.time() > beta.time())
      xb += vb * (alpha.time() - beta.time());
    else
      xa += va * (beta.time() - alpha.time());

    double time = std :: max(alpha.time(), beta.time());

    bool close;
    double beg;
    double end;

    double a = ~(va - vb);
    double b = 2. * (xa - xb) * (va - vb);
    double c = ~(xa - xb) - radiisquared;


    if(c < 0)
    {
      // Molecules are already close

      close = true;
      beg = time;
    }
    else
    {
      close = false;

      // Test 1: molecules approaching

      if(b >= 0)
      {
        this->_happens = false;
        return;
      }

      // Test 2: collision range

      double beg = newton :: quadratic(a, b, c, time);

      if(std :: isnan(beg))
      {
        this->_happens = false;
        return;
      }
    }

    // Determine end of collision range

    double mid = time + sqrt(~(xa - xb) / ~(va - vb)); // Maximum proximity of molecules centers of mass
    double beyond = 2. * mid - beg; // Parabolas are symmetric

    end = close ? newton :: quadratic(a, b, c, beyond) : beyond;

    double step = 0.5 * std :: min(std :: min(M_PI / fabs(alpha.angular_velocity() + beta.angular_velocity()), M_PI / fabs(alpha.angular_velocity() - beta.angular_velocity())), std :: min(M_PI / fabs(2. * alpha.angular_velocity()), M_PI / fabs(2. * beta.angular_velocity())));
    // TODO: Find out better euristics for maximum cropping of minima and maxima?

    // Look for collisions between atoms

    for(double binbeg = beg; binbeg < end; binbeg += step)
    {
      double binend = std :: min(binbeg + step, end);

      for(size_t i = 0; i < alpha.size(); i++)
        for(size_t j = 0; j < beta.size(); j++)
        {
          double ctime = collision(alpha, i, beta, j, binbeg, binend);

          if(!std :: isnan(ctime))
          {
            this->_happens = true;
            this->_time = ctime;

            this->_alpha.molecule = &alpha;
            this->_alpha.atom = i;
            this->_alpha.version = alpha.version();

            this->_beta.molecule = &beta;
            this->_beta.atom = j;
            this->_beta.version = beta.version();

            return;
          }
        }
    }

    this->_happens = false;
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

  double molecule_molecule :: collision(const molecule & alpha, const size_t & index_alpha, const molecule & beta, const size_t & index_beta, const double & beg, const double & end)
  {
    double radiisquared = (alpha[index_alpha].radius() + beta[index_beta].radius()) * (alpha[index_alpha].radius() + beta[index_beta].radius());

    auto distsquared = [&](const double & time)
    {
      return ~(position(alpha, index_alpha, time) - position(beta, index_beta, time)) - radiisquared;
    };

    double binmin = gss :: min(distsquared, beg, end);

    if(distsquared(binmin) > 0)
      return NaN;

    double binmax = gss :: max(distsquared, beg, end);
    return secant :: compute(distsquared, binmax, binmin);
  }
};
