#include "window.h"

// Constructors

window :: window(const char * title, int width, int height, int position_x, int position_y, lockpick :: color background, int frame_width_percentage, int frame_height_percentage) : lockpick :: window(title, width, height, position_x, position_y, background, frame_width_percentage, frame_height_percentage)
{
}

// Methods

void window :: draw(const molecule & molecule)
{
  for(size_t i = 0; i < molecule.size(); i++)
  {
    vec position = molecule.position() + molecule[i].position() % molecule.orientation();
    this->circle({position.x, position.y}, molecule[i].radius());
  }
}
