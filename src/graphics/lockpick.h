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

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <cmath>
#include <cstring>
#include <iostream>

// Includes

#include "molecule/atom.h"
#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "elements/bumper.h"

#ifdef _MSC_VER
  #ifndef __unused
  #define __unused
  #endif
#else
  #ifndef __unused
  #define __unused __attribute__((__unused__))
  #endif
#endif

__unused std :: mutex mtx; // mutex for critical section

__unused const char * __default_title = const_cast <char *> ("nocs");
__unused constexpr int __default_width = 750;
__unused constexpr int __default_height = 750;
__unused constexpr int __triangle_amount = 40;
__unused constexpr double __twice_pi = 2.0f * M_PI;

namespace graphics
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

  struct sphere
  {
    // Members

    vector center;
    double radius;
    color c;

    // Constructor

    sphere();
    sphere(vector center, double radius, color c = {0, 0, 1});

    // Destructor

    ~sphere() = default;
  };

  struct line
  {
    // Members

    vector beg;
    vector end;
    color c;

    // Constructor

    line();
    line(vector beg, vector end, color c = {1, 0, 0});

    // Destructor

    ~line() = default;
  };

  __unused std :: vector <sphere> sphere_buffer;
  __unused std :: vector <line> line_buffer;
  __unused std :: atomic <bool> request_drawing(false);

  class window
  {
    // Members

    int _id;
    std :: thread _th;

  protected:

    // Static members

    static bool __started;
    static int __window_count;

  public:

    // Constructors

    window();

    // Destructor

    ~window();

    // Static methods

    static void draw(const engine &);
    static void draw(const engine &, const uint8_t &);
    static void wait_click();
    static void flush();
    static void clear();

  private:

    // Static private methods

    static void start();
    static void render();
    static void timer(int);
    static void thread_wait_click();
    static void draw_line(__unused line);
    static void draw_circle(__unused sphere);

    static void list_sphere(const molecule &);
    static void list_sphere(const bumper &);
    static void grid(const engine &);
  };

}

#endif
