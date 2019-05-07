#include "dispatcher.h"
#include "event/events/molecule.h"
#include "event/events/bumper.h"

// Methods

size_t dispatcher :: add(callback <events :: molecule> * event)
{
  size_t id = autoincrement++;

  this->_molecule.types.add(id, all);
  this->_molecule.all.add(id, event);

  return id;
}

size_t dispatcher :: add(callback <events :: molecule> * event, const uint8_t & tag)
{
  size_t id = autoincrement++;

  this->_molecule.types.add(id, stag);
  this->_molecule.stag.handles.add(id, std :: tuple <callback <events :: molecule> *, uint8_t> (event, tag));
  this->_molecule.stag.map[tag].add(event);

  return id;
}

size_t dispatcher :: add(callback <events :: molecule> * event, const uint8_t & alpha, const uint8_t & beta)
{
  size_t id = autoincrement++;

  this->_molecule.types.add(id, dtag);
  this->_molecule.dtag.handles.add(id, std :: tuple <callback <events :: molecule> *, uint8_t, uint8_t> (event, alpha, beta));
  this->_molecule.dtag.map[alpha][beta].add(event);

  if(alpha != beta)
    this->_molecule.dtag.map[beta][alpha].add(event);

  return id;
}

size_t dispatcher :: add(callback <events :: bumper> * event)
{
  size_t id = autoincrement++;

  this->_bumper.types.add(id, all);
  this->_bumper.all.add(id, event);

  return id;
}

size_t dispatcher :: add(callback <events :: bumper> * event, const uint8_t & tag)
{
    size_t id = autoincrement++;

    this->_bumper.types.add(id, stag);
    this->_bumper.stag.handles.add(id, std :: tuple <callback <events :: bumper> *, uint8_t> (event, tag));
    this->_bumper.stag.map[tag].add(event);

    return id;
}

void dispatcher :: trigger(const events :: molecule & event)
{
  auto trigger = [&](callback <events :: molecule> * callback)
  {
    callback->trigger(event);
  };

  this->_molecule.all.each(trigger);

  bool striggered[255];
  memset(striggered, '\0', 255 * sizeof(bool));

  for(size_t i = 0; i < event.alpha().tag.size(); i++)
    if(!striggered[event.alpha().tag[i]])
    {
      striggered[event.alpha().tag[i]] = true;
      this->_molecule.stag.map[event.alpha().tag[i]].each(trigger);
    }

  for(size_t i = 0; i < event.beta().tag.size(); i++)
    if(!striggered[event.beta().tag[i]])
    {
      striggered[event.beta().tag[i]] = true;
      this->_molecule.stag.map[event.beta().tag[i]].each(trigger);
    }

  bool dtriggered[255][255];
  for(size_t i = 0; i < 255; i++)
    memset(dtriggered[i], '\0', 255 * sizeof(bool));

  for(size_t i = 0; i < event.alpha().tag.size(); i++)
    for(size_t j = 0; j < event.beta().tag.size(); j++)
    {
      if(!dtriggered[event.alpha().tag[i]][event.beta().tag[j]])
      {
        dtriggered[event.alpha().tag[i]][event.beta().tag[j]] = true;
        dtriggered[event.beta().tag[j]][event.alpha().tag[i]] = true;

        this->_molecule.dtag.map[event.alpha().tag[i]][event.beta().tag[j]].each(trigger);
      }
    }
}

void dispatcher :: trigger(const events :: bumper & event)
{
  auto trigger = [&](callback <events :: bumper> * callback)
  {
    callback->trigger(event);
  };

  this->_bumper.all.each(trigger);

  bool striggered[255];
  memset(striggered, '\0', 255 * sizeof(bool));

  for(size_t i = 0; i < event.molecule().tag.size(); i++)
  {
    striggered[event.molecule().tag[i]] = true;
    this->_bumper.stag.map[event.molecule().tag[i]].each(trigger);
  }
}

template <> void dispatcher :: remove <events :: molecule> (const size_t & id)
{
  switch(this->_molecule.types[id])
  {
    case all:
    {
      this->_molecule.all.remove(id);
      break;
    }
    case stag:
    {
      auto handle = this->_molecule.stag.handles[id];

      this->_molecule.stag.handles.remove(id);
      this->_molecule.stag.map[std :: get <1> (handle)].remove(std :: get <0> (handle));

      break;
    }
    case dtag:
    {
      auto handle = this->_molecule.dtag.handles[id];

      this->_molecule.dtag.handles.remove(id);
      this->_molecule.dtag.map[std :: get <1> (handle)][std :: get <2> (handle)].remove(std :: get <0> (handle));
      this->_molecule.dtag.map[std :: get <2> (handle)][std :: get <1> (handle)].remove(std :: get <0> (handle));

      break;
    }
  }

  this->_molecule.types.remove(id);
}

template <> void dispatcher :: remove <events :: bumper> (const size_t & id)
{
  switch(this->_bumper.types[id])
  {
    case all:
    {
      this->_bumper.all.remove(id);
      break;
    }
    case stag:
    {
      auto handle = this->_bumper.stag.handles[id];

      this->_bumper.stag.handles.remove(id);
      this->_bumper.stag.map[std :: get <1> (handle)].remove(std :: get <0> (handle));

      break;
    }
    default:
    {
    }
  }
}

// Private static members

size_t dispatcher :: autoincrement;
