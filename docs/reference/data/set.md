## Class `set`

### Overview

Class `set` is a polymorphic implementation of the set data structure.

### Interface

#### Constructor

  * `template <typename type> set <type> :: set()`

    builds a set with the given type.

#### Destructor

  * `template <typename type> set <type> :: ~set()`

    destroys the set.

#### Methods

  * `void add(const type & element)`

    inserts the given element into the set.

  * `const type & remove(const type & element)`

    removes the element from the set.

  * `template <typename lambda, typename std :: enable_if <valid <lambda> :: value> :: type * = nullptr> void each(const lambda & function) const`

    given a lambda `function` that takes as argument a variable of the same type of the set, executes the lambda function over each element of the set.
