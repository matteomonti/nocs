#ifdef __main__

#include <iostream>

#include "math/newton.h"

int main()
{
  double s = 0;
  unsigned long int i = 0;
  for(double c = -2.; c > -12.; c -= 1.e-9, i++)
  {
    if(i%1000000==0) std::cout<<i<<std::endl;
    s += newton :: quadratic(1, 0, c, -1);
  }
  std :: cout << "Completed:" << s << std :: endl;
}

#endif
