#ifndef __lockpick__
#define __lockpick__

// Libraries

#ifdef __graphics__

#define LIGHT

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <GL/freeglut.h>
#endif // __graphics__

#include <thread>
#include <cmath>
#include <cstring>
#include <iostream>

#ifdef _MSC_VER
  #define __unused
#else
  #define __unused __attribute__((__unused__))
#endif

__unused static const char * __default_title = const_cast <char *> ("nocs");
__unused static const int __default_width = 750;
__unused static const int __default_height = 750;
__unused static const int __triangle_amount = 20;


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

    // Destructor

    ~vector() = default;
  };

  struct color
  {
    // Members

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    // Constructor

    color();
    color(unsigned char red, unsigned char green, unsigned char blue);


    // Destructor

    ~color() = default;
  };

  class window
  {
    // Members

    int _id;
    std::thread _th;

  protected:

    // Static members

    static bool __started;
    static int __window_count;

  public:

    // Constructors

    window(const char * title = nullptr, int width = __default_width, int height = __default_height, int position_x = 0, int position_y = 0, color background = color(255, 255, 255), int frame_width_percentage = 95, int frame_height_percentage = 95);

    // Destructor

    ~window();

    // Methods

    void line(vector from, vector to);
    void circle(vector center, double radius, color c = {0, 0, 1});

    // Static methods

    static void wait_enter();
    static void wait_click();
    static void flush();
    static void dummy_flush();
    static void clear();

    void start();

  private:

    // Static private methods

    void run();
  };

}

#endif
