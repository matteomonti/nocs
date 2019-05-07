## Class `secant`

### Overview

Class `secant` implements the secant method for a generic lambda function that takes a `double` as argument.

### Example usage

```c++
auto function = [&](const double & x)
{
  return x * x - 4;
}

std :: cout << secant :: compute(function, -5, 0) << std :: endl; // Prints -2
std :: cout << secant :: compute(function, -0, 5) << std :: endl; // Prints 2
```

### Interface

#### Static members

 * `static constexpr double epsilon`
    
    machine epsilon considered for the computation

 * `static constexpr unsigned int rounds`
    
    maximum number of iterations before forced timeout

#### Static methods

 * `static double compute(const lambda & function, double lower_bound, double upper_bound)`
    
    using secant method, returns the zero of function inside the range [lower_bound, upper_bound].
    
    **REMARK: works only if in the given range the zero is unique and the function is monotonic**
