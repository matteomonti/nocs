#include "lockpick.h"

bool __enter__ = false;
bool __click__ = false;

namespace graphics
{
  // vector

  // Constructors

  vector :: vector()
  {
    this->x = 0.;
    this->y = 0.;
  }

  vector :: vector(double x, double y)
  {
    this->x = x;
    this->y = y;
  }

  // color

  // Constructors

  color :: color()
  {
  }

  color :: color(unsigned char red, unsigned char green, unsigned char blue)
  {
    this->red = red;
    this->green = green;
    this->blue = blue;
  }

  // sphere

  sphere :: sphere(vector center, double radius, color c): center(center), radius(radius), c(c)
  {}

  // line

  line :: line(vector beg, vector end, color c): beg(beg), end(end), c(c)
  {}

  // window

  // Constructors

  window :: window()
  {
#ifdef __graphics__
    if (!__started)
    {
      _th = std :: thread(window :: start);
    }
#endif
  }

  // Destructor

  window :: ~window()
  {
#ifdef __graphics__
    _th.join();
    --__window_count;
    _id = glutGetWindow();
    glutLeaveMainLoop();

    if (__window_count == 0)
    {
      glutDestroyWindow(_id);
      __started = false;
    }
#endif
  }

  // Static methods

  void window :: draw(const engine &engine)
  {
    mtx.lock();
    line_buffer.clear();
    sphere_buffer.clear();
    window :: grid(engine);
    engine.each<molecule>([&](const molecule &molecule) {
      window :: list_sphere(molecule);
    });

    engine.each<bumper>([&](const bumper &bumper) {
      window :: list_sphere(bumper);
    });
    mtx.unlock();
  }

  void window :: draw(const engine &engine, const uint8_t &tag)
  {
    mtx.lock();
    line_buffer.clear();
    sphere_buffer.clear();
    window :: grid(engine);
    engine.each<molecule>(tag, [&](const molecule &molecule) {
      window :: list_sphere(molecule);
    });
    mtx.unlock();
  }

  void window :: wait_click()
  {
#ifdef __graphics__
    window :: thread_wait_click();
#endif
  }

  void window :: flush()
  {
#ifdef __graphics__
    request_drawing = true;
#endif
  }

  // Static private methods

  void window :: start()
  {
#ifdef __graphics__
    int myargc = 1;
    char *myargv[1];
    myargv[0] = strdup("nocs");
    glutInit(&myargc, myargv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow(__default_title);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.f, 1.f, 0.f, 1.f); // xmin, xmax, ymin, ymax
    glutDisplayFunc(window :: render);
    glutTimerFunc(0, window :: timer, 0);
    glutMouseFunc([](int button, __unused int state, __unused int x, __unused int y) {
      switch (button)
      {
      case GLUT_LEFT_BUTTON:
        __click__ = true;
        break;
      default:
        __click__ = false;
        break;
      }
    });
    // Set range coordinates
    __started = true;
    glutMainLoop();
#endif
  }

  void window :: render()
  {
#ifdef __graphics__
    if (request_drawing)
    {
      mtx.lock();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
      glLoadIdentity(); // Reset the projection matrix

      for (auto it = line_buffer.begin(); it != line_buffer.end(); it++)
      {
        draw_line(*it);
      }
      for (auto it = sphere_buffer.begin(); it != sphere_buffer.end(); it++)
      {
        draw_circle(*it);
      }

      glutSwapBuffers();

      request_drawing = false;
      mtx.unlock();
    }

#endif
  }

  void window :: timer(__unused int extra)
  {
#ifdef __graphics__
    glutPostRedisplay();
    glutTimerFunc(1, window :: timer, 0);
#endif
  }

  void window :: thread_wait_click()
  {
#ifdef __graphics__
    __click__ = false;
    while (true)
    {
      if (__click__)
        break;
      std :: this_thread :: sleep_for(std :: chrono :: milliseconds(50));
    }
#endif
  }

  void window :: draw_line(__unused line l)
  {
#ifdef __graphics__
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.f, 1.f, 0.f, 1.f); // xmin, xmax, ymin, ymax

    glBegin(GL_LINE_STRIP);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(GLdouble(l.beg.x), GLdouble(l.beg.y), GLdouble(0.));
    glVertex3d(GLdouble(l.end.x), GLdouble(l.end.y), GLdouble(0.));
    glEnd();
#endif
  }

  void window :: draw_circle(__unused sphere c)
  {
#ifdef __graphics__
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.f, 1.f, 0.f, 1.f); // xmin, xmax, ymin, ymax
    

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(c.center.x, c.center.y); // center of circle
    for (int i = 0; i <= __triangle_amount; i++)
    {
      glColor3f(c.c.red, c.c.green, c.c.blue);
      glVertex2f(
          c.center.x + (c.radius * std :: cos(i * __twice_pi / __triangle_amount)),
          c.center.y + (c.radius * std :: sin(i * __twice_pi / __triangle_amount)));
    }
    glEnd();
#endif
  }

  // Static members

  bool window :: __started = false;
  int window :: __window_count = 0;

  void window :: list_sphere(const molecule &molecule)
  {
    for (size_t i = 0; i < molecule.size(); i++)
    {
      vec position = molecule.position() + molecule[i].position() % molecule.orientation();

      for (double dx : {1., 0., -1.})
        for (double dy : {1., 0., -1.})
          sphere_buffer.push_back(sphere({dx + position.x, dy + position.y}, molecule[i].radius()));
    }
  }

  void window :: list_sphere(const bumper &bumper)
  {
    for (double dx : {1., 0., -1.})
      for (double dy : {1., 0., -1.})
        sphere_buffer.push_back(sphere({dx + bumper.position().x, dy + bumper.position().y}, bumper.radius(), {1, 0, 0}));
  }

  void window :: grid(const engine &engine)
  {
    double step = 1. / engine.fineness();
    for (size_t i = 1; i < engine.fineness(); i++)
    {
      line_buffer.push_back(line({step * i, 0.}, {step * i, 1.}));
      line_buffer.push_back(line({0., step * i}, {1., step * i}));
    }
  }
}
