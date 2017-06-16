#include "resetter.h"
#include "engine.h"
#include "molecule/molecule.h"

// energy

resetter :: energy :: energy(engine & engine) : _engine(engine)
{
}

// Methods

void resetter :: energy :: id(const size_t & id, const double & target)
{
  molecule * molecule = this->_engine._molecules[id];
  molecule->scale_energy(target);
  this->_engine.refresh(*molecule);
}

void resetter :: energy :: tag(const uint8_t & tag, const double & target)
{
  double energy = 0;
  this->_engine._tags[tag].each([&](molecule * molecule)
  {
    energy += molecule->energy();
  });

  this->_engine._tags[tag].each([&](molecule * molecule)
  {
    molecule->scale_energy(molecule->energy() * target / energy);
    this->_engine.refresh(*molecule);
  });
}

void resetter :: energy :: all(const double & target)
{
  double energy = 0;
  this->_engine._molecules.each([&](molecule * molecule)
  {
    energy += molecule->energy();
  });

  this->_engine._molecules.each([&](molecule * molecule)
  {
    molecule->scale_energy(molecule->energy() * target / energy);
    this->_engine.refresh(*molecule);
  });
}

// resetter

// Private constructors

resetter :: resetter(engine & engine) : _engine(engine), energy(engine)
{
}
