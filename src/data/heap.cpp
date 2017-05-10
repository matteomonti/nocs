#include "heap.h"

// Constructors

heap :: heap()
{
  this->_size = 0;
  this->_events = new event * [settings :: capacity];
}

// Destructor

heap :: ~heap()
{
    delete [] this->_events;
}

// Getters

const size_t & heap :: size()
{
  return this->_size;
}

// Methods

void heap :: push(event * event)
{
  this->_size++;
  this->_events[this->_size] = event;
  this->bubble_up(this->_size);
}

event * heap :: peek()
{
  if (this->_size == 0)
    return(NULL);

  return (this->_events[1]);
}

event * heap :: pop()
{
  if (this->_size == 0)
    return(NULL);
    
  event * event = this->_events[1];

  this->_events[1] = this->_events[this->_size];
  this->_size--;

  this->bubble_down(1);

  return event;
}

// Private methods

void heap :: swap(const size_t & i, const size_t & j)
{
  event * swap = this->_events[i];
  this->_events[i] = this->_events[j];
  this->_events[j] = swap;
}

void heap :: bubble_up(const size_t & i)
{
  if(i == 1)
    return;

  if(this->_events[i]->time() < this->_events[i / 2]->time())
  {
    this->swap(i, i / 2);
    this->bubble_up(i / 2);
  }
}

void heap :: bubble_down(const size_t & i)
{
  if(i * 2 > this->_size)
    return;

  if(this->_events[i]->time() > this->_events[i * 2]->time() || this->_events[i]->time() > this->_events[i * 2 + 1]->time())
  {
    if(this->_events[i*2]->time() < this->_events[i * 2 + 1]->time())
    {
      this->swap(i, i * 2);
      this->bubble_down(i * 2);
    }
    else
    {
      this->swap(i, i * 2 + 1);
      this->bubble_down(i * 2 + 1);
    }
  }
}
