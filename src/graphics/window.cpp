#include "window.h"

// Constructors

window :: window(const char * title, int width, int height, int position_x, int position_y, lockpick :: color background, int frame_width_percentage, int frame_height_percentage) : lockpick :: window(title, width, height, position_x, position_y, background, frame_width_percentage, frame_height_percentage)
{
}

// Methods

void window :: draw(const engine & engine)
{
  engine.each <molecule> ([&](const molecule & molecule)
  {
    this->draw(molecule);
  });

  engine.each <bumper> ([&](const bumper & bumper)
  {
    this->draw(bumper);
  });
}

void window :: draw_with_grid(const engine & engine)
{
  this->grid(engine);
  engine.each <molecule> ([&](const molecule & molecule)
  {
    this->draw(molecule);
  });

  engine.each <bumper> ([&](const bumper & bumper)
  {
    this->draw(bumper);
  });
}

void window :: draw(const engine & engine, const uint8_t & tag)
{
  engine.each <molecule> (tag, [&](const molecule & molecule)
  {
    this->draw(molecule);
  });
}

void window :: draw(const molecule & molecule)
{
  for(size_t i = 0; i < molecule.size(); i++)
  {
    vec position = molecule.position() + molecule[i].position() % molecule.orientation();

    for(double dx : {1., 0., -1.})
      for(double dy : {1., 0., -1.})
        this->circle({dx + position.x, dy + position.y}, molecule[i].radius());
  }
}

void window :: draw(const bumper & bumper)
{
  for(double dx : {1., 0., -1.})
    for(double dy : {1., 0., -1.})
      this->circle({dx + bumper.position().x, dy + bumper.position().y}, bumper.radius());
}

// Private methods

void window :: grid(const engine & engine)
{
  double step = 1. / engine.fineness();
  for(size_t i = 1; i < engine.fineness(); i++)
  {
    this->line({step * i, 0.}, {step * i, 1.});
    this->line({0., step * i}, {1., step * i});
  }
}
