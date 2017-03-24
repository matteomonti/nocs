#include "molecule.h"

// Constructors

molecule :: molecule()
{
}

molecule :: molecule(const std :: vector<atom> & atoms, const vec & position, const vec & velocity, const double & orientation, const double & angular_velocity) :  _position(position), _velocity(velocity), _orientation(orientation), _angular_velocity(angular_velocity)
{
	this->_mass = 0;
	this->_size = atoms.size();
	this->_atoms = new atom[this->_size];
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_atoms[i] = atoms[i];
		this->_mass += this->_atoms[i].mass();
	}

	/*NOTA :: cdm -> (sum m_i*r_i / sum m_i)*/
	vec v(0, 0);
	for (size_t i = 0; i < this->_size; i++)
		v += this->_atoms[i].mass() * this->_atoms[i].position();

	for (size_t i = 0; i < this->_size; i++)
		this->_atoms[i].move(this->_atoms[i].position() - v);

	this->_inertia_moment = 0;
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_inertia_moment += this->_atoms[i].mass() * (std :: pow(this->_atoms[i].radius(), 2) + ~this->_atoms[i].position());
	}
}

molecule :: molecule(const molecule & m) : _size(m.size()), _mass(m.mass()), _inertia_moment(m.inertia_moment()), _position(m.position()), _velocity(m.velocity()), _orientation(m.orientation()), _angular_velocity(m.angular_velocity())
{
	for (size_t i = 0; i < this->_size; i++)
		this->_atoms[i] = m.atoms(i);
}

molecule :: ~molecule()
{
	delete[] this->_atoms;
}

// Getters

const size_t & molecule :: size() const
{
	return this->_size;
}

const atom & molecule :: atoms(const size_t & n) const
{
	return this->_atoms[n];
}

const double & molecule :: mass() const
{
	return this->_mass;
}

const double & molecule :: inertia_moment() const
{
	return this->_inertia_moment;
}

const vec & molecule :: position() const
{
	return this->_position;
}

const vec & molecule :: velocity() const
{
	return this->_velocity;
}

const double & molecule :: orientation() const
{
	return this->_orientation;
}

const double & molecule :: angular_velocity() const
{
	return this->_angular_velocity;
}

const double & molecule :: time() const
{
	return this->_time;
}

const unsigned int & molecule :: version() const
{
	return this->_version;
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const molecule & m)
{
	/*KEEP IT UPDATED, CHARLIE!*/
	return out << "Position:\t(" << m.position().x << ", " << m.position().y << ")" << std :: endl
			   << "Mass:\t" << m.mass() << std :: endl;
}
