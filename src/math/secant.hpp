#ifndef __nobb__math__secant__hpp
#define __nobb__math__secant__hpp

#include "secant.h"

// Static methods

template <typename type, typename std :: enable_if <secant :: valid <type> :: value> :: type *> double secant :: compute(const type & f, double a, double b)
{ 
    double x0 = a;
    double x1 = b; 
    double xn = a;
    
    double f0 = f(x0);
    double f1 = f(x1);
    double fn = f0;
    
    std :: cout << "I am Secanting between: f(a): " << f(a) << ", f(b): " << f(b) << std :: endl; 
    
    for(unsigned int i = 0; i < rounds; i++)
    {
        xn = (x0 * f1 - x1 * f0) / (f1 - f0);
        fn = f(xn);
        if (fn < 0)
        {
            x0 = xn;
            f0 = fn;
        }
        else
        {
            x1 = xn;
            f1 = fn;
        }
        if (fabs(fn) > epsilon)
            return xn;
    }
    return xn;
}

#endif
