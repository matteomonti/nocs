#ifndef __nobb__engine__engine__hpp
#define __nobb__engine__engine__hpp

#include "engine.h"
#include "molecule/molecule.h"

// Methods

template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type *> void engine :: each(const lambda & callback) const
{
  this->_molecules.each([&](molecule * molecule)
  {
    molecule->integrate(this->_time);
    callback((const class molecule &) (*molecule));
  });
}

template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type *> void engine :: each(const uint8_t & tag, const lambda & callback) const
{
  this->_tags[tag].each([&](molecule * molecule)
  {
    molecule->integrate(this->_time);
    callback((const class molecule &) (*molecule));
  });
}

template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, bumper> :: value> :: type *> void engine :: each(const lambda & callback) const
{
  this->_bumpers.each([&](bumper * bumper)
  {
    callback((const class bumper &) (*bumper));
  });
}

template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type *> size_t engine :: on(const lambda & callback)
{
  :: callback <etype> * wrapper = new :: callback <etype, lambda> (callback);
  return this->_dispatcher.add(wrapper);
}

template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type *> size_t engine :: on(const uint8_t & tag, const lambda & callback)
{
  :: callback <etype> * wrapper = new :: callback <etype> (callback);
  return this->_dispatcher.add(wrapper, tag);
}

template <typename etype, typename lambda, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value> :: type *> size_t engine :: on(const uint8_t & alpha, const uint8_t & beta, const lambda & callback)
{
  :: callback <etype> * wrapper = new :: callback <etype> (callback);
  return this->_dispatcher.add(wrapper, alpha, beta);
}

template <typename etype, typename std :: enable_if <std :: is_same <etype, events :: molecule> :: value || std :: is_same <etype, events :: bumper> :: value> :: type *> void engine :: unsubscribe(const size_t & id)
{
  this->_dispatcher.remove <etype> (id);
}

#endif
