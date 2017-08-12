## Class `engine`

### Overview

Class `engine` represents the core of the entire simulation and takes care of the actual execution of the processes simulated. By storing the objects of the simulation and by building a queue of event objects, the simulation is executed in all its parts. It also provides a subscription system that allows the user to "subscribe" to the desired events of the simulation, in order to gather only the required data without wasting computational time.

### Public nested classes

#### `class tag`

Class `tag` is what allows to identify any object of the simulation with a series of system-defined and user-defined tags. By including this class inside the implementation of an object like `molecule`, it is possible to distinguish any typology of `molecule` with any desired tag.

**Constructor**

  * `tag()`
    builds the object

**Getters**

  * `const size_t & id() const`
    gets the id tag.

  * `const size() const`
    gets the number of tags that characterizes the object.

  * `const size_t & references() const`
    gets the number of references that the object has inside the queue of events inside the engine. (this element is fundamental for the correct implementation of the **resetter** mechanism).

**Operators**

  * `unit8_t operator [] (const size_t & i) const`
    returns the i-th tag.

### Interface

#### Public memebers

  * `resetter reset`
    see documentation about **resetter** for more informations.

#### Constructors

  * `engine(const size_t & fineness)`
    builds an engine with a grid of given fineness.

#### Destructor

  * `~engine()`
    destroys the engine.

#### Getters

  * `const size_t & fineness() const`
    gets the fineness of the engine's grid.

#### Setters

  * `void elasticity(const double & elasticity)`
    sets the elasticity for all the collisions between molecules.

  * `void elasticity(const unit8_t & tag, const double & elasticity)`
    sets the elasticity for all the collisions that involve a molecule with the given tag

  * `void elasticity(const unit8_t & alpha_tag, const unit8_t & beta_tag, const double & elasticity)`
    sets the elasticity for all the collisions that involve two molecules with the given `alpha_tag` and `beta_tag`, respectively.

#### Methods

  * `size_t add(const molecule & molecule)`
    adds the given molecule to the engine. Returns the id of the molecule, given by the engine.

  * `size_t add(const bumper & bumper)`
    adds the given bumper to the engine. Returns the id of the bumper, given by the engine.

  * `void remove(const size_t & id)`
    removes the molecule with the given id form the engine.

  * `void tag(const size_t & id, const unit8_t & tag)`
    assigns the given tag to the molecule with the given id.

  * `void untag(const size_t & id, const unit8_t & tag)`
    removes the given tag from the molecule with the given id.

  * `void run(const double & time)`
    executes the simulation **UNTIL** the given time.

  * `template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type * = nullptr> void each(const lambda & function) const`
    given a lambda function that takes for argument a `molecule`, it executes the lambda function to each `molecule` inside the engine.

  * `template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type * = nullptr> void each(const uint8_t & tag, const lambda & function) const`
    given a lambda function that takes for argument a `molecule`, it executes the lambda function to each `molecule` inside the engine that has the given tag.

  * `template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, bumper> :: value> :: type * = nullptr> void each(const lambda & function) const`
    given a lambda function that takes for argument a `bumper`, it executes the lambda function to each `bumper` inside the engine.

  * `template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type * = nullptr> size_t on(const lambda & function)`
    given a lambda function that takes as argument a `const report <events :: molecule>` or a `const report <events :: bumper>`, the engine registers it as a subscription and will execute it from now on with all the events of the chosen type. Returns the id of the subscription.

  * `template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type * = nullptr> size_t on(const uint8_t & tag, const lambda & function)`
    given a lambda function that takes as argument a `const report <events :: molecule>` or a `const report <events :: bumper>`, the engine registers it as a subscription and will execute it from now on with all the events of the chosen type that involve a molecule with the given tag. Returns the id of the subscription.

  * `template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value> :: type * = nullptr> size_t on(const uint8_t & alpha_tag, const uint8_t & beta_tag, const lambda & function)`
    given a lambda function that takes as argument a `const report <events :: molecule>`, the engine registers it as a subscription and will execute it from now on with all the `event :: molecule`s that involve two molecules with the given tags. Returns the id of the subscription.

  * `template <typename etype, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type * = nullptr> void unsubscribe(const size_t & id);`
    given the id of the subscription, cancels the subscription.
