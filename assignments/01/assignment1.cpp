#include <GL/glut.h>
#include <GL/gl.h>

void render(void);
void drawNinjaHead(void);
void drawNinjaBody(void);
void drawNinjaArms(void);
void drawNinjaLegs(void);
void drawNinjaWeapon(void);

/*
 * Written by Robert "Chip" Senkbeil
 * Uses -lglut and -lGL to compile on Linux.
 * Displays a ninja with goggles and a spear.
 */
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 640);
  glutCreateWindow(argv[0]);

  //glutReshapeFunc(/* ... */);
  //glutKeyboardFunc(/* ... */);
  //glutMouseFunc(/* ... */);
  //glutMotionFunc(/* ... */);
  glutDisplayFunc(render);

  glutMainLoop();
  return 0;
}

/**
 * Renders the graphics onto the screen.
 * Uses:
 * GL_QUADS
 * glColor
 */
void render(void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* Background color is dark red */
  glClearColor(0.5f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* Color of ninja body is black */
  glColor3f(1.0f, 1.0f, 1.0f);

  /* Draw a white square on top of the red background */
  glBegin(GL_QUADS);
    glVertex3f(-0.8f, -0.8f, 0.0f);
    glVertex3f(0.8f, -0.8f, 0.0f);
    glVertex3f(0.8f, 0.8f, 0.0f);
    glVertex3f(-0.8f, 0.8f, 0.0f);
  glEnd();

  drawNinjaHead();
  drawNinjaBody();
  drawNinjaArms();
  drawNinjaLegs();
  drawNinjaWeapon();
 
  glutSwapBuffers();
}

/*
 * Uses:
 * GL_QUAD_STRIP
 * GL_POINTS
 * GL_LINE_LOOP
 * glPointSize
 * glColor
 */
void drawNinjaHead(void) {
  /* Draw the head base */
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_QUAD_STRIP);
    glVertex3f(-0.1f, 0.75f, 0.0f);
    glVertex3f(0.1f, 0.75f, 0.0f);
    glVertex3f(-0.3f, 0.65f, 0.0f);
    glVertex3f(0.3f, 0.65f, 0.0f);
    glVertex3f(-0.1f, 0.55f, 0.0f);
    glVertex3f(0.1f, 0.55f, 0.0f);
  glEnd();

  /* Draw the eyes */
  glPointSize(10.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_POINTS);
    glVertex3f(-0.1f, 0.65f, 0.0f); // Left eye
    glVertex3f(0.1f, 0.65f, 0.0f); // Right eye
  glEnd();
  glPointSize(1.0f); // Reset the point size

  /* Draw the glasses */
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
    glVertex3f(-0.15f, 0.70f, 0.0f);
    glVertex3f(0.15f, 0.70f, 0.0f);
    glVertex3f(0.15f, 0.60f, 0.0f);
    glVertex3f(-0.15f, 0.60f, 0.0f);
  glEnd();
}

/*
 * Uses:
 * GL_POLYGON
 * GL_LINE_STRIP
 * glColor
 */
void drawNinjaBody(void) {
  glColor3f(0.0f, 0.0f, 0.0f);
  
  /* Draw the neck and body of the ninja */
  glBegin(GL_POLYGON);
    glVertex3f(-0.05f, 0.55f, 0.0f);
    glVertex3f(0.05f, 0.55f, 0.0f);
    glVertex3f(0.2f, 0.45f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 0.0f, 0.0f);
    glVertex3f(-0.2f, 0.45, 0.0f);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
    glVertex3f(0.15f, 0.35f, 0.0f);
    glVertex3f(-0.15f, 0.35f, 0.0f);
    glVertex3f(-0.15f, 0.15f, 0.0f);
    glVertex3f(0.15f, 0.15f, 0.0f);
  glEnd();
}

/*
 * Uses:
 * GL_TRIANGLE_STRIPS
 * GL_TRIANGLE_FAN
 * glColor
 */
void drawNinjaArms(void) {
  glColor3f(0.0f, 0.0f, 0.0f);

  /* Draw right arm */
  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.1f, 0.40f, 0.0f);
    glVertex3f(0.6f, 0.35f, 0.0f);
    glVertex3f(0.7f, 0.40f, 0.0f); 
    glVertex3f(0.6f, 0.45f, 0.0f);
  glEnd();

  /* Draw left arm */
  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-0.1f, 0.40f, 0.0f); 
    glVertex3f(-0.6f, 0.35f, 0.0f); 
    glVertex3f(-0.6f, 0.45f, 0.0f);
    glVertex3f(-0.7f, 0.40f, 0.0f); 
  glEnd();
}

/*
 * Uses:
 * GL_QUADS
 * glColor
 */
void drawNinjaLegs(void) {
  glColor3f(0.0f, 0.0f, 0.0f);

  /* Draw the two legs fused together */
  glBegin(GL_QUADS);
    glVertex3f(-0.1f, 0.0f, 0.0f);
    glVertex3f(0.1f, 0.0, 0.0f);
    glVertex3f(0.1f, -0.7f, 0.0f);
    glVertex3f(-0.1f, -0.7f, 0.0f);
  glEnd();
}

/*
 * Uses:
 * GL_LINES
 * GL_TRIANGLES
 * glLineThickness
 * glColor
 */
void drawNinjaWeapon(void) {
  glColor3f(0.0f, 0.0f, 0.0f);
  
  /* Draw the pole the ninja uses */
  glLineWidth(5.0f);
  glBegin(GL_LINES);
    glVertex3f(-0.7f, -0.6f, 0.0f);
    glVertex3f(-0.7f, 0.6f, 0.0f);
  glEnd();
  glLineWidth(1.0f);

  /* Draw the spear head on top of the pole */
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.75f, 0.6f, 0.0f);
    glVertex3f(-0.65f, 0.6f, 0.0f);
    glVertex3f(-0.70f, 0.8f, 0.0f);
  glEnd();
}

