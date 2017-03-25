#include "collision.h"

// Constructors

collision :: collision() : event()
{
}

collision :: collision(molecule * m1, molecule * m2) : event(), _m1(m1), _m2(m2)
{
  e1 = this->_m1->version();
  e2 = this->_m2->version();

  // mi metto nel sistema di riferimento inerziale di m2 e considero la velocità di m1
  vec v = this->_m1->velocity() - this->_m2->velocity();
  v /= !v;
  // considero il vettore direzione m2 - m1
  vec x = this->_m2->position() - this->_m1->position();
  double n = v * x;

  // prima scrematura :: se si stanno distanziando li scarto
  if(n <= 0)
    this->_happens = false;
  else
  {
    double d = !x;
    double f = pow(d, 2) - pow(n, 2);
    double s = pow(this->_m1->radius() + this->_m2->radius(), 2)

    // seconda scrematura, se non si toccano...
    if(f >= s)
      this->_happens = false;
      else
      {
        double p = s - f;

        // si toccheranno nel contorno esteriore dopo...
        double t = (d - sqrt(p)) / (this->_m1->velocity() - this->_m2->velocity());

        // TODO :: in questo punto
        // -> analisi seria ed estremamente pesante...
      }
  }
  // alla fine o abbiamo _happens = false e si butta via tutto
  // o abbiamo _happens = true con tutti i dati ben allocati
}

// Virtual Methods Override

void collision :: compute()
{
  //integrazione del moto e calcolo dell'URTO
  //aggiornamento della versione delle molecole e del loro tempo
}

bool collision :: version_control()
{
  return e1 == this->_m1->version() && e2 == this->_m2->version();
}
