#include "lockpick.h"

namespace lockpick
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

  // glcircle

  // Constructors

  window :: _glcircle :: _glcircle() : buf(nullptr)
  {
  }

  window :: _glcircle :: _glcircle(unsigned int subdivs) : subdivs(subdivs + 2)
  {
    this->buf = new double[this->subdivs];
    this->buf[0] = 0.;
    this->buf[1] = 0.;
    for (unsigned int i = 0; i <= subdivs; i++)
    {
      double angle = i * ((2. * M_PI) / subdivs);
      this->buf[i + 2] = std :: cos(angle);
      this->buf[i + 3] = std :: sin(angle);
    }
  }

  // Destructor

  window :: _glcircle :: ~_glcircle()
  {
    delete[] this->buf;
  }

  // Operators

  window :: _glcircle & window :: _glcircle :: operator=(window :: _glcircle g)
  {
    this->subdivs = g.subdivs;
    this->buf = new double[this->subdivs];
    std :: memcpy(this->buf, g.buf, sizeof(double)*this->subdivs);
    return *this;
  }


  // circle

  // Constructors

  window :: _circle :: _circle()
  {
    _size = 0.;
    _x = 0.;
    _y = 0.;
    _scale = 0.;
  }

  window :: _circle :: _circle(vector pos, double scale, color c, unsigned int size) : _size(size), _c(c), _scale(scale)
  {
    _x = pos.x;
    _y = pos.y;
  }

  window :: _circle :: _circle(unsigned int size) : _size(size)
  {
    _x = 0.;
    _y = 0.;
    _scale = 0.;
  }

  // Members

  void window :: _circle :: draw(__attribute__((unused)) vector center, __attribute__((unused)) double scale, __attribute__((unused)) color c)
  {
#ifdef __graphics__
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);                         // To operate on model-view matrix
                                                        // Clear window and null buffer Z
                                                        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                        // Reset transformation
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef( center.x, center.y, 0 );
    glScalef( scale, scale, 0 );
    glColor3ub( c.red, c.green, c.blue );
    glDrawArrays( GL_TRIANGLE_FAN, 0, _size );
    glPopMatrix();
#endif
  }

  // window

  // Constructors

  window :: window(__attribute__((unused)) const char * title, __attribute__((unused)) int width, __attribute__((unused)) int height, __attribute__((unused)) int position_x, __attribute__((unused)) int position_y, __attribute__((unused)) color background, __attribute__((unused)) int frame_width_percentage, __attribute__((unused)) int frame_height_percentage)
  {
#ifdef __graphics__
    start();
    ++__window_count;

    if (title)
    {
      glutCreateWindow(title);
      glutInitWindowPosition(position_x, position_y);
      glClearColor(1.f, 1.f, 1.f, 1.f);
    }

    frame_width_percentage = (frame_width_percentage << 24) + (background.red << 16) + (background.green << 8) + background.blue;
    frame_height_percentage = (frame_height_percentage << 24) + (width << 11) + height;

    // MISS set the coordinate range
    __ball = _circle(11);
    __glball = _glcircle(20);

    glutInitWindowSize( frame_width_percentage, frame_height_percentage );
    _id = glutGetWindow() - 1;
#endif
  }

  // Destructor

  window :: ~window()
  {
#ifdef __graphics__
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

  // Methods

  void window :: line(__attribute__((unused)) vector from, __attribute__((unused)) vector to)
  {
#ifdef __graphics__
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);                         // To operate on model-view matrix
                                                        // Clear window and null buffer Z
                                                        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                        // Reset transformation
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(from.x, from.y, 0.);
    glVertex3f(to.x, to.y, 0.);
    glEnd();
#endif
  }

  void window :: circle(__attribute__((unused)) vector center, __attribute__((unused)) double radius, __attribute__((unused)) color c)
  {
#ifdef __graphics__
    __ball.draw(center, radius, c);
#endif
  }


  // Static methods

  void window :: set_default_title(const char * title)
  {
    __default_title = const_cast <char *> (title);
  }

  void window :: set_default_size(int width, int height)
  {
    __default_width = width;
    __default_height = height;
  }

  void window :: wait_enter()
  {
  #ifdef __graphics__

  #endif
  }

  void window :: wait_click()
  {
  #ifdef __graphics__

  #endif
  }

  void window :: flush()
  {
#ifdef __graphics__
    glutSwapBuffers();
    glFlush();
#endif
  }

  void window :: clear()
  {
#ifdef __graphics__
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
    glLoadIdentity();                                   // Reset the projection matrix
#endif
  }

  // Static private methods

  void window :: start()
  {
#ifdef __graphics__
    if (!__started)
    {
      __started = true;
      int myargc = 1;
      char * myargv[1];
      myargv[0] = strdup("nocs");
      glutInit(&myargc, myargv);
#if defined(LIGHT)
      glEnable(GL_LIGHT0);                                    // Turn on a light with defaults set
      glEnable(GL_LIGHTING);                                  // Turn on lighting
      glEnable(GL_COLOR_MATERIAL);
      glShadeModel(GL_SMOOTH);                                // Allow color
#endif // LIGHT
      glClearColor(0.0, 0.0, 0.0, 1);                         // window background in RGB
      glViewport(0, 0, __default_width, __default_height);    // Make our viewport the whole window
      glMatrixMode(GL_PROJECTION);                            // Select The Projection Matrix
      glLoadIdentity();                                       // Reset The Projection Matrix
      glMatrixMode(GL_MODELVIEW);                             // Select The Modelview Matrix
      glLoadIdentity();                                       // Reset The Modelview Matrix
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
      glLoadIdentity();                                       // Reset The View
      glEnable(GL_DEPTH_TEST);

      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
      // Create window
      glutInitWindowSize( __default_width, __default_height );
      glutInitWindowPosition(10, 10);
      glutCreateWindow(__default_title);
      glClearColor(1.f, 1.f, 1.f, 1.f);
      glutDisplayFunc(flush);
      //glutSpecialFunc(wait_enter);
      //glutSpecialFunc(wait_click);
      // Control OpenGL events
      glutMainLoop();                                         // Enter the infinite event-processing loop
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
