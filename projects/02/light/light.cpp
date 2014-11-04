
#include <GL/gl.h>
#include "light.h"

// Attributes for light 0 (color is white)
float position0[] = {-4.0f, 10.0f, 25.0f, 1.0f};
float diffuse0[]  = {0.8f, 0.8f, 0.8f, 1.0f};
float ambient0[]  = {0.3f, 0.3f, 0.3f, 0.0f};
float specular0[] = {1.0f, 1.0f, 1.0f, 1.0f};
 
// Attributes for light 1 (color is blue)
float position1[] = {4.0f, 10.0f, 25.0f, 1.0f};
float diffuse1[]  = {0.0f, 0.0f, 0.8f, 1.0f};
float ambient1[]  = {0.0f, 0.0f, 0.3f, 1.0f};
float specular1[] = {0.0f, 0.0f, 1.0f, 1.0f};

void setupLight(void) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
}

