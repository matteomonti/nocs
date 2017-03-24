#include <molecule.h>

/* ATOM */

// Constructors

atom :: atom()
{
}

atom :: atom(vec position, double radius, double mass) : position(position), radius(radius), mass(mass)
{
}

// Public Methods

vec atom :: getPosition() const
{
	return position;
}

double atom :: getRadius() const
{
	return radius;
}

double atom :: getMass() const
{
	return mass;
}

void atom :: move(vec v)
{
	position += v;
}

void atom :: move(double x, double y)
{
	position.x += x;
	position.y += y;
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const atom & a)
{
	return out << "Position:\t(" << a.getPosition().x << ", " << a.getPosition().y << ")" << std :: endl
			   << "Radius:\t" << a.getRadius() << std :: endl
			   << "Mass:\t" << a.getMass() << std :: endl;
}

/* MOLECULE */

// Constructors

molecule :: molecule()
{
}

molecule :: molecule(std :: vector<atom> atoms_list,
					 vec position, vec velocity,
					 double orientation, double angular_velocity) : position(position), velocity(velocity), orientation(orientation), angular_velocity(angular_velocity)
{
	mass = 0;
	size = atoms_list.size();
	atoms = new atom[size];
	for (unsigned int i = 0; i < size; i++)
	{
		atoms[i] = atoms_list[i];
		mass += atoms[i].getMass();
	}

	correctposition();

	angular_mass = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		/*NOTE :: massa inerzia disco I = mr^2*/
		/* teorema assi paralleli : I + md^2*/
		angular_mass += atoms[i].getMass() * (std :: pow(atoms[i].getRadius(), 2) + ~atoms[i].getPosition());
	}
}

molecule :: molecule(std :: vector<atom> atoms_list)
{
	mass = 0;
	size = atoms_list.size();
	atoms = new atom[size];
	for (unsigned int i = 0; i < size; i++)
	{
		atoms[i] = atoms_list[i];
		mass += atoms[i].getMass();
	}

	correctposition();

	angular_mass = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		angular_mass += atoms[i].getMass() * (std :: pow(atoms[i].getRadius(), 2) + ~atoms[i].getPosition());
	}

	/*TODO(maybe?) :: collocazione randomica*/
}

molecule :: molecule(const molecule & m) : size(m.getSize()), mass(m.getMass()), angular_mass(m.getAngular_mass()), position(m.getPosition()), velocity(m.getVelocity()), orientation(m.getOrientation()), angular_velocity(m.getAngular_velocity())
{
	for (unsigned int i = 0; i < size; i++)
		atoms[i] = m.atoms[i];
}

molecule :: ~molecule()
{
	delete[] atoms;
}

// Public Methods

size_t molecule :: getSize() const
{
	return size;
}

atom molecule :: getAtom(unsigned int n) const
{
	return atoms[n];
}

double molecule :: getMass() const
{
	return mass;
}

double molecule :: getAngular_mass() const
{
	return angular_mass;
}

vec molecule :: getPosition() const
{
	return position;
}

vec molecule :: getVelocity() const
{
	return velocity;
}

double molecule :: getOrientation() const
{
	return orientation;
}

double molecule :: getAngular_velocity() const
{
	return angular_velocity;
}

double molecule :: getTime() const
{
	return time;
}

unsigned int molecule :: getVersion() const
{
	return version;
}

// Private Methods

vec molecule :: getcdm()
{
	/*NOTA :: cdm -> (sum m_i*r_i / sum m_i)*/
	double x, y;
	x = 0;
	y = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		x += atoms[i].getMass() * atoms[i].getPosition().x;
		y += atoms[i].getMass() * atoms[i].getPosition().y;
	}
	return vec(x / mass, y / mass);
}

void molecule :: correctposition()
{
	vec cdm = getcdm();
	for (unsigned int i = 0; i < size; i++)
		atoms[i].move(-cdm); /*TODO :: INSERT MINUS OPERATOR*/
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const molecule & m)
{
	/*KEEP IT UPDATED, CHARLIE!*/
	return out << "Position:\t(" << m.getPosition().x << ", " << m.getPosition().y << ")" << std :: endl
			   << "Mass:\t" << m.getMass() << std :: endl;
}
