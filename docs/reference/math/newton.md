## Class `newton`

### Overview

Class `newton` implements the Newton-Raphson algorithm for a generic parabola `y = a*x^2 + b*x + c`.

### Example usage

```c++
std :: cout << newton :: quadratic(0, 0, 2) << std :: endl; // Prints NaN
std :: cout << newton :: quadratic(0, 0, -4, -1) << std :: endl; // Prints -2
```

### Interface

#### Static members

 * `static constexpr double epsilon`
    
    machine epsilon considered for the computation

 * `static constexpr unsigned int rounds`
    
    maximum number of iterations before forced timeout

#### Static methods

 * `double quadratic(const double & a, const double & b, const double & c, double starting_point = 0)`
    
    using Newton-Raphson method, returns the zero of the parabola `y = a*x^2 + b*x + c`.
    
    **REMARK: if the parabola has no zeros, the function returns a NaN**
