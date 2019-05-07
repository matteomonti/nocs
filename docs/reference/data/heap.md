## Class `heap`

### Overview

Class `heap` is a polymorphic implementation of the heap data structure.

### Interface

#### Constructor

  * `template <typename type> heap <type> :: heap()`

    builds an heap with the given type.

#### Destructor

  * `template <typename type> heap <type> :: ~heap()`

    destroys the heap.

#### Getters

  * `size()`

#### Methods

  * `void push(const type & element)`

    inserts the given element inside the heap.

  * `const type & peek() const`

    returns the last element of the heap without modifying the heap.

  * `type pop()`

    returns the last element of the heap and removes it from the heap.
