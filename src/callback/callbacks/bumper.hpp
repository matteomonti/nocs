#ifndef __nobb__callback__callbacks__bumper__hpp
#define __nobb__callback__callbacks__bumper__hpp

#include "bumper.h"
#include "event/reports/bumper.h"

// Constructors

template <typename lambda> callback <events :: bumper, lambda> :: callback(const lambda & callback) : _callback(callback)
{
}

// Methods

template <typename lambda> void callback <events :: bumper, lambda> :: trigger(const events :: bumper & event)
{
  this->_callback(report <events :: bumper> (event));
}

#endif
