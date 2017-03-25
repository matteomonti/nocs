#include "molecule.h"

// Constructors

molecule :: molecule()
{
}

molecule :: molecule(const std :: vector<atom> & atoms, const vec & position, const vec & velocity, const double & orientation, const double & angular_velocity) :  _position(position), _velocity(velocity), _orientation(orientation), _angular_velocity(angular_velocity)
{
	this->_time = 0;
	this->_version = 0;
	this->_mass = 0;
	this->_size = atoms.size();
	this->_atoms = new atom[this->_size];

	for (size_t i = 0; i < this->_size; i++)
	{
		this->_atoms[i] = atoms[i];
		this->_mass += this->_atoms[i].mass();
	}

	/*NOTA :: com -> (sum m_i*r_i / sum m_i)*/
	vec com(0, 0);
	for (size_t i = 0; i < this->_size; i++)
		com += this->_atoms[i].mass() * this->_atoms[i].position();

	com /= this->_mass;

	for (size_t i = 0; i < this->_size; i++)
		this->_atoms[i].move(this->_atoms[i].position() - com);

	this->_radius = 0;
	for (size_t i = 0; i < this->_size; i++)
		this->_radius = std :: max(this->_radius, !this->_atoms[i].position() + this->_atoms[i].radius());

	this->_inertia_moment = 0;

	for (size_t i = 0; i < this->_size; i++)
		this->_inertia_moment += this->_atoms[i].mass() * (std :: pow(this->_atoms[i].radius(), 2) + ~this->_atoms[i].position());
}

molecule :: molecule(const molecule & m) : _size(m.size()), _mass(m.mass()), _inertia_moment(m.inertia_moment()), _position(m.position()), _velocity(m.velocity()), _orientation(m.orientation()), _angular_velocity(m.angular_velocity())
{
	for (size_t i = 0; i < this->_size; i++)
		this->_atoms[i] = m[i];
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

const double & molecule :: radius() const
{
	return this->_radius;
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

// Public Operators

const atom & molecule :: operator [] (const size_t & n) const
{
	return this->_atoms[n];
}

// Public Nested Classes

// Constructors

molecule :: printer :: printer()
{
}

molecule :: printer :: printer(std :: ostream & out) : out(& out)
{
	(*(this->out)) << std :: endl << "-----CARATTERISTICHE MOLECOLE-----" << std :: endl << "m\tI\tq\tv\ttheta\tomega\tt\tversion" << std :: endl;
}

// Operators

molecule :: printer & molecule :: printer :: operator << (const molecule & m)
{
	(*(this->out)) <<  m.mass() << "\t" << m.inertia_moment() << "\t" << m.position() << "\t" << m.velocity() << "\t" << m.orientation() << "\t" << m.angular_velocity() << "\t" << m.time() << "\t" << m.version() << std :: endl;
	return *this;
}

template <typename type> std :: ostream & molecule :: printer :: operator << (const type & x)
{
	return (*(this->out)) << x;
}

// Standard Output

molecule :: printer & operator << (std :: ostream & out, const molecule & m)
{
	return molecule :: printer(out) << m;
}
