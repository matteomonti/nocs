## Class `gss`

### Overview

Class `gss` implements a generic Golden Section Search valid for any lambda function that takes a `double` as argument.

### Example usage

```c++
auto function = [&](const double & x)
{
  return x * x;
}

std :: cout << gss :: max(function, -1, 2) << std :: endl; // Prints 2
std :: cout << gss :: min(function, -1, 2) << std :: endl; // Prints 0
```

### Interface

#### Static members

 * `static constexpr double epsilon`
    
    machine epsilon considered for the computation

 * `static constexpr unsigned int rounds`
    
    maximum number of iterations before forced timeout

#### Static methods

 * `static double min(const lambda & function, double lower_bound, double upper_bound)`
    
    given a valid function, returns the minimum of function in the range [lower_bound, upper_bound].
    
    **REMARK: this only works if the minimum is unique inside the given range**

 * `static double max(const lambda & function, double lower_bound, double upper_bound)`
    
    given a valid function, returns the maximum of function in the range [lower_bound, upper_bound].
    
    **REMARK: this only works if the maximum is unique inside the given range**
