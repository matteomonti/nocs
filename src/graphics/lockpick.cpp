#include "lockpick.h"

namespace lockpick
{
  // vector

  // Constructors

  vector :: vector()
  {
  #ifdef __graphics__
    x = 0.;
    y = 0.;
  #endif
  }

  vector :: vector(double x, double y)
  {
  #ifdef __graphics__
    this->x = x;
    this->y = y;
  #endif
  }

  // color

  // Constructors

  color :: color()
  {
  }

  color :: color(unsigned int red, unsigned int green, unsigned int blue)
  {
  #ifdef __graphics__
    this->red = red;
    this->green = green;
    this->blue = blue;
  #endif
  }

  // window

  // Constructors

  window :: window(const char * title, int width, int height, int position_x, int position_y, color background, int frame_width_percentage, int frame_height_percentage)
  {
  #ifdef __graphics__
    start();
    ++__window_count;

    if(title)
    {
        int position[] = {position_x, position_y};
        m_place_window(position, const_cast <char *> (title));
    }

    frame_width_percentage = (frame_width_percentage << 24) + (background.red << 16) + (background.green << 8) + background.blue;
    frame_height_percentage = (frame_height_percentage << 24) + (width << 11) + height;
    _id = m_window(&frame_width_percentage, &frame_height_percentage) - 1;

    double xmin = 0., ymin = 0., xmax = 1., ymax = 1.;
    m_frame(&xmin, &ymin, &xmax, &ymax);
  #endif
  }

  // Destructor

  window :: ~window()
  {
  #ifdef __graphics__
    --__window_count;
    m_close(&_id);

    if(__window_count == 0)
    {
        m_endg();
        __started = false;
    }
  #endif
  }

  // Methods

  void window :: ellipse(vector center, vector axes, bool fill)
  {
  #ifdef __graphics__
    m_select(&_id);

    double vcenter[2] = {center.x, center.y};
    double vaxes[2] = {axes.x, axes.y};

    int mode = fill;
    m_ellipse(vcenter, vaxes, &mode);
  #endif
  }

  void window :: arc(vector center, vector axes, double initial_ang, double amp, double incl, bool fill)
  {
  #ifdef __graphics__
    m_select (&_id);

    double vcenter[2] = {center.x, center.y};
    double vaxes[2] = {axes.x, axes.y};
    double ang[3] = {initial_ang, amp, incl};

    int mode = fill;
    m_arc(vcenter, vaxes, ang, &mode);
  #endif
  }

  void window :: circle(vector center, double radius, bool fill, int c)
  {
  #ifdef __graphics__
    colors(c);
    ellipse(center, {radius, radius}, fill);
  #endif
  }

  void window :: line(vector from, vector to)
  {
  #ifdef __graphics__
    m_select(&_id);

    double vfrom[2] = {from.x, from.y};
    m_move(vfrom);

    double vto[2] = {to.x, to.y};
    m_line(vto);
  #endif
  }

  void window :: text(char * c, vector x)
  {
  #ifdef __graphics__
    m_select(&_id);
    double vx[2] = {x.x, x.y};

    m_text(c, vx);
  #endif
  }

  void window :: colors (int n)
  {
  #ifdef __graphics__
    m_select(&_id);
    m_color(&n);
  #endif
  }

  // Static methods

  void window :: set_default_title(const char * title)
  {
  #ifdef __graphics__
    __default_title = const_cast <char *> (title);
  #endif
  }

  void window :: set_default_size(int width, int height)
  {
  #ifdef __graphics__
    __default_width = width;
    __default_height = height;
  #endif
  }

  void window :: wait_enter()
  {
  #ifdef __graphics__
    int event = EVENTO_ENTER;
    m_wait_for_events(&event);
  #endif
  }

  void window :: wait_click()
  {
  #ifdef __graphics__
    int event = EVENTO_MOUSE;
    m_wait_for_events(&event);
  #endif
  }

  void window :: flush()
  {
  #ifdef __graphics__
    m_redraw(&_id);
  #endif
  }

  void window :: clear()
  {
  #ifdef __graphics__
    m_clear(&_id);
  #endif
  }

  // Static private methods

  void window :: start()
  {
  #ifdef __graphics__
    if(!__started)
    {
        __started = true;
        m_startg(__default_title, &__default_width, &__default_height);
    }
  #endif
  }

  // Static members

  bool window :: __started = false;
  char * window :: __default_title = const_cast <char *> ("Lockpick");
  int window :: __default_width = 750;
  int window :: __default_height = 750;
  int window :: __window_count = 0;
}
