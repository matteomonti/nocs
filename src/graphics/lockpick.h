#ifndef __lockpick__
#define __lockpick__

// Libraries
#if defined (__linux__) || defined (__apple__)
#include <unistd.h>
#endif

#ifdef __graphics__
#include <passe_par_tout.h>
#endif

namespace lockpick
{
  struct vector
  {
      // Members

      double x;
      double y;

      // Constructors

      vector();
      vector(double x, double y);
  };

  struct color
  {
    // Members

    unsigned int red, green, blue;

    // Constructors

    color();
    color(unsigned int red, unsigned int green, unsigned int blue);
  };

  class window
  {
    // Members

    int _id;

  protected:

    // Static members

    static bool __started;

    static char * __default_title;
    static int __default_width;
    static int __default_height;

    static int __window_count;

  public:

    // Constructors

    window(const char * title = nullptr, int width = __default_width, int height = __default_height, int position_x = 0, int position_y = 0, color background = color(255, 255, 255), int frame_width_percentage = 95, int frame_height_percentage = 95);

    // Destructor

    ~window();

    // Methods

    void ellipse(vector center, vector axes, bool fill = false);
    void arc(vector center, vector axes, double initial_ang, double amp, double incl = 360, bool fill = false);
    void circle(vector center, double radius, bool fill = false, int c = 0);
    void line(vector from, vector to);
    void text(char * c, vector x);
    void colors(int n);

    // Static methods

    static void set_default_title(const char * title);
    static void set_default_size(int width, int height);
    static void wait_enter();
    static void wait_click();
    void flush();
    void clear();

  private:

    // Static private methods

    static void start();
  };
}

#endif
