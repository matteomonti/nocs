#ifndef __nobb__callback__callbacks__molecule__hpp
#define __nobb__callback__callbacks__molecule__hpp

#include "molecule.h"
#include "event/reports/molecule.h"

// Constructors

template <typename lambda> callback <events :: molecule, lambda> :: callback(const lambda & callback) : _callback(callback)
{}

// Methods

template <typename lambda> void callback <events :: molecule, lambda> :: trigger(const events :: molecule & event)
{
  this->_callback(report <events :: molecule>(event));
}

#endif
