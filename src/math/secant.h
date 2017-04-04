// Forward declarations

class secant;

#if !defined(__forward__) && !defined(__nobb__math__secant__h)
#define __nobb__math__secant__h

// Libraries

#include <cmath>
#include <limits>
#include <type_traits>
#include <stdint.h>

class secant
{
  // Service nested classes

  template <typename type> struct valid
  {
    template <typename vtype> struct helper
    {
    };

    template <typename vtype> static uint8_t sfinae(...);
    template <typename vtype> static uint32_t sfinae(helper <decltype((* (const typename std :: remove_reference <vtype> :: type *) nullptr)(0.))> *);

    template <bool, bool> struct conditional;

    template <bool dummy> struct conditional <true, dummy>
    {
      static constexpr bool value = std :: is_same <typename std :: remove_reference <decltype((* (const typename std :: remove_reference <type> :: type *) nullptr)(0.))> :: type, double> :: value;
    };

    template <bool dummy> struct conditional <false, dummy>
    {
      static constexpr bool value = false;
    };

    static constexpr bool value = (conditional <sizeof(sfinae <type> (0)) == sizeof(uint32_t), false> :: value);
  };

public:

  // Static members

  static constexpr double epsilon = 5. * std :: numeric_limits <double> :: epsilon();

  // Static methods

  template <typename type, typename std :: enable_if <valid <type> :: value> :: type * = nullptr> static double compute(const type &, double, double);
};

#endif