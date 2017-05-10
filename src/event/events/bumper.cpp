#include "bumper.hpp"

namespace events
{
  // Constructors

  bumper :: bumper (molecule & molecule, :: bumper & bumper, const int & fold)
  {
    vec xa = molecule.position();
    vec xb = bumper.position() + vec(fold);

    vec v = molecule.velocity();

    double radiisquared = (molecule.radius() + bumper.radius()) * (molecule.radius() + bumper.radius());

    double time = molecule.time();

    bool close;
    double beg;
    double end;

    double a = ~v;
    double b = 2. * (xa - xb) * v;
    double c = ~(xa - xb) - radiisquared;

    if(c < 0)
    {
      // Bumper and Molecule are already close

      close = true;
      beg = time;
    }
    else
    {
      close = false;

      // Test 1: molecule approaching

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

    double mid = time + sqrt(~(xa - xb) / ~v); // Maximum proximity of molecules centers of mass
    double beyond = 2. * mid - beg; // Parabolas are symmetric

    end = close ? (time + newton :: quadratic(a, b, c, beyond - time)) : beyond;

    double step = 0.5 * M_PI / fabs(2. * molecule.angular_velocity()); // TODO: find if this cropping can be used also for this kind of event.

    // Look for collisions between atoms and bumper

    this->_time = std :: numeric_limits <double> :: infinity();

    for(double binbeg = beg; binbeg < end; binbeg += step)
    {
      double binend = std :: min(binbeg + step, end);

      for(size_t i = 0; i < molecule.size(); i++)
      {
        double ctime = collision(molecule, i, bumper, binbeg, binend, fold);

        if(!std :: isnan(ctime) && ctime < this->_time)
        {
          this->_time = ctime;
          this->_molecule.atom = i;
        }
      }

      if(this->_time < std :: numeric_limits <double> :: infinity())
      {
        this->_happens = true;
        this->_molecule.molecule = &molecule;
        this->_molecule.version = molecule.version();
        this->_bumper = &bumper;
        this->_fold = fold;

        return;
      }
    }

    this->_happens = false;
  }

  // Getters

  molecule & bumper :: mol()
  {
    return *(this->_molecule.molecule);
  }

  // Methods

  bool bumper :: current()
  {
    return this->_molecule.version == this->_molecule.molecule->version();
  }

  void bumper :: resolve()
  {
    // Check version

    if(!current())
      return;

    // Integrate to collision

    this->_molecule.molecule->integrate(this->_time);

    // Update version

    (*(this->_molecule.molecule))++;

    // Collision resolution

    vec a = position(*(this->_molecule.molecule), this->_molecule.atom);
    vec b = this->_bumper->position() + vec(this->_fold);

    vec n = (a - b).normalize(); // Versor of the impulse from bumper to molecule

    double m = this->_molecule.molecule->mass();
    double i = this->_molecule.molecule->inertia_moment();
    double w = this->_molecule.molecule->angular_velocity();
    vec v = this->_molecule.molecule->velocity();

    vec r = (*(this->_molecule.molecule))[this->_molecule.atom].position() % this->_molecule.molecule->orientation() + (*(this->_molecule.molecule))[this->_molecule.atom].radius() * (-n);

    double module = (2 * v * n + 2 * w * (r ^ n)) / -(1 / m + ((r ^ n) * (r ^ n)) / i); // Module of the impulse (I Hope...)

    // Update molecule velocity and angular_velocity

    this->_molecule.molecule->impulse(r, module * n);
  }

  // Private Methods

  void bumper :: print() const
  {
    std :: cout << "Event bumper at time: " << this->_time;
  }

  double bumper :: collision(const molecule & molecule, const size_t & index, const :: bumper & bumper, const double & beg, const double & end, const int & fold)
  {
    double radiisquared = (molecule[index].radius() + bumper.radius()) * (molecule[index].radius() + bumper.radius());

    auto distsquared = [&](const double & time)
    {
      return ~(position(molecule, index, time) - (bumper.position() + vec(fold))) - radiisquared;
    };

    double binmin = gss :: min(distsquared, beg, end);

    if(distsquared(binmin) > 0)
      return NaN;

    double binmax = gss :: max(distsquared, beg, binmin);

    return secant :: compute(distsquared, binmax, binmin);
  }
};
