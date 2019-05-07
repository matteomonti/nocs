## Class `dispatcher`

### Overview

Class `dispatcher` has the duty to keep track of all the subscription requests to the various kind of events that can occur. By keeping various typologies of subscriptions in different hashtables, `dispatcher` wraps all the given lambda function and returns them when the correct trigger is activated.

### Interface

#### Methods

  * `size_t add(callback <events :: molecule> * function)`

    given a lambda function correctly wrapped with its `callback` class, adds it to the event molecule subscription list. Returns the id of the subscription.

  * `size_t add(callback <events :: molecule> * function, const unit8_t & tag)`

    given a lambda function correctly wrapped with its `callback` class, adds it to the event molecule subscription list related to the given tag. Returns the id of the subscription.

  * `size_t add(callback <events :: molecule> *, const unit8_t & alpha_tag, const unit8_t & beta_tag)`

    given a lambda function correctly wrapped with its `callback` class, adds it to the event molecule subscription list related to the given alpha_tag and beta_tag. Returns the id of the subscription.

  * `size_t add(callback <events :: bumper> * function)`

    given a lambda function correctly wrapped with its `callback` class, adds it to the event bumper subscription list. Returns the id of the subscription.

  * `size_t add(callback <events :: bumper> * function, const unit8_t & tag)`

    given a lambda function correctly wrapped with its `callback` class, adds it to the event bumper subscription list related to the given tag. Returns the id of the subscription.

  * `void trigger(const events :: molecule & event)`

    given an event molecule, sets off all the related lambda function subscribed.

  * `void trigger(const events :: bumper & event)`

    given an event bumper, sets off all the related lambda function subscribed.

  * `template <typename etype> void remove(const size_t & id)`

    given a subscription id, removes the subscription.
