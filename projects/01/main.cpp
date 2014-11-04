#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "camera.h"
#include "robot.h"

const int MENU_NORMAL_MODE     = 0;
const int MENU_ZOOM_MODE       = 1;
const int MENU_PAN_MODE        = 2;
const int MENU_HEAD            = 3;
const int MENU_NECK            = 4;
const int MENU_UPPER_TORSO     = 5;
const int MENU_LOWER_TORSO     = 6;
const int MENU_PELVIS          = 7;
const int MENU_LEFT_SHOULDER   = 8;
const int MENU_RIGHT_SHOULDER  = 9;
const int MENU_LEFT_UPPER_ARM  = 10;
const int MENU_RIGHT_UPPER_ARM = 11;
const int MENU_LEFT_LOWER_ARM  = 12;
const int MENU_RIGHT_LOWER_ARM = 13;
const int MENU_LEFT_HAND       = 14;
const int MENU_RIGHT_HAND      = 15;
const int MENU_LEFT_UPPER_LEG  = 16;
const int MENU_RIGHT_UPPER_LEG = 17;
const int MENU_LEFT_LOWER_LEG  = 18;
const int MENU_RIGHT_LOWER_LEG = 19;
const int MENU_LEFT_FOOT       = 20;
const int MENU_RIGHT_FOOT      = 21;

const float DISTANCE = 50.0f;

int buildPopupMenu(void);
void arrowPress(int key, int x, int y);
void mouseEvent(int button, int state, int x, int y);
void mouseMoveEvent(int x, int y);
void menuEvent(int id);
void render(void);
void terminate_prog(void);

// Mode variables
int currentMode = 0;

// Mouse variables
bool isPressed = false;
bool isPanning = false;
int oldX = 0;
int oldY = 0;

// The robot drawn on the screen
Robot* robot;
Camera camera;

/*
 * Written by Robert "Chip" Senkbeil
 * Uses -lglut, -lGLU, and -lGL to compile on Linux.
 */
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 640);
  glutCreateWindow(argv[0]);
  glEnable(GL_DEPTH_TEST);

  //glutReshapeFunc(/* ... */);
  glutSpecialFunc(arrowPress);
  glutMouseFunc(mouseEvent);
  glutMotionFunc(mouseMoveEvent);
  glutDisplayFunc(render);
  //glutIdleFunc(render);

  // Build and attach the menu
  buildPopupMenu();
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // Allocate memory for a new robot
  printf("Allocating new robot...\n");
  robot = new Robot();

  printf("Setting up the camera...\n");
  camera.setCameraMaxDistance(4.0f);
  //camera.lock();

  // Set termination callback
  atexit(terminate_prog);

  // Start the main loop
  glutMainLoop();

  // Exit program
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
  gluPerspective(90.0f, 640.0f/640.0f, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* Background color is black */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Update camera */
  camera.update();
 
  /* Render the robot */
  robot->render();

  /* Swap the buffers to display changes */
  glutSwapBuffers();
}

/**
 * Generates and returns the id to the menu to be used.
 */
int buildPopupMenu(void) {
  int menu;
  menu = glutCreateMenu(menuEvent);
  glutAddMenuEntry("Enable Normal Mode", MENU_NORMAL_MODE);
  glutAddMenuEntry("Enable Zoom Mode", MENU_ZOOM_MODE);
  glutAddMenuEntry("Enable Pan Mode", MENU_PAN_MODE);
  glutAddMenuEntry("Enable Head Changing", MENU_HEAD);
  glutAddMenuEntry("Enable Neck Changing", MENU_NECK);
  glutAddMenuEntry("Enable Upper Torso Changing", MENU_UPPER_TORSO);
  glutAddMenuEntry("Enable Lower Torso Changing", MENU_LOWER_TORSO);
  glutAddMenuEntry("Enable Pelvis Changing", MENU_PELVIS);
  glutAddMenuEntry("Enable Left Shoulder Changing", MENU_LEFT_SHOULDER);
  glutAddMenuEntry("Enable Left Upper Arm Changing", MENU_LEFT_UPPER_ARM);
  glutAddMenuEntry("Enable Left Lower Arm Changing", MENU_LEFT_LOWER_ARM);
  glutAddMenuEntry("Enable Left Hand Changing", MENU_LEFT_HAND);
  glutAddMenuEntry("Enable Right Shoulder Changing", MENU_RIGHT_SHOULDER);
  glutAddMenuEntry("Enable Right Upper Arm Changing", MENU_RIGHT_UPPER_ARM);
  glutAddMenuEntry("Enable Right Lower Arm Changing", MENU_RIGHT_LOWER_ARM);
  glutAddMenuEntry("Enable Right Hand Changing", MENU_RIGHT_HAND);
  glutAddMenuEntry("Enable Left Upper Leg Changing", MENU_LEFT_UPPER_LEG);
  glutAddMenuEntry("Enable Left Lower Leg Changing", MENU_LEFT_LOWER_LEG);
  glutAddMenuEntry("Enable Left Foot Changing", MENU_LEFT_FOOT);
  glutAddMenuEntry("Enable Right Upper Leg Changing", MENU_RIGHT_UPPER_LEG);
  glutAddMenuEntry("Enable Right Lower Leg Changing", MENU_RIGHT_LOWER_LEG);
  glutAddMenuEntry("Enable Right Foot Changing", MENU_RIGHT_FOOT);

  return menu;
}

/**
 * Keyboard callback
 */
void arrowPress(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      //camera.panLeft(1);
      break;

    case GLUT_KEY_RIGHT:
      //camera.panRight(1);
      break;

    case GLUT_KEY_UP:
      //camera.zoomIn(0.1f);
      break;

    case GLUT_KEY_DOWN:
      //camera.zoomOut(0.1f);
      break;
  }
  glutPostRedisplay();
}

/**
 * Callback for mouse events.
 */
void mouseEvent(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        oldX = x;
        oldY = y;
        isPressed = true;
      }
      if (state == GLUT_UP) {
        oldX = 0;
        oldY = 0;
        isPressed = false;
      }
      break;
  }
}

/**
 * Callback for mouse movement events.
 */
void mouseMoveEvent(int x, int y) {
  if (isPressed) {
    int changeInX = x - oldX;
    int changeInY = y - oldY;

    // Check to see what kind of event should take place
    switch (currentMode) {
      case MENU_NORMAL_MODE:
        camera.rotateRight(changeInX);
        camera.rotateUp(changeInY);
        break;

      case MENU_ZOOM_MODE:
        if (changeInY > 0)
          camera.zoomIn(0.01f);
        if (changeInY < 0)
          camera.zoomOut(0.01f);
        break;

      case MENU_PAN_MODE:
        camera.panRight(changeInX);
        break;

      case MENU_HEAD:
        robot->setAngle("HEAD", 
                        robot->getAngleH("HEAD") + changeInY, 
                        robot->getAngleV("HEAD") + changeInX);
        break;

      case MENU_NECK:
        robot->setAngle("NECK", 
                        robot->getAngleH("NECK") + changeInY, 
                        robot->getAngleV("NECK") + changeInX);
        break;

      case MENU_UPPER_TORSO:
        robot->setAngle("UPPER_TORSO", 
                        robot->getAngleH("UPPER_TORSO") + changeInY, 
                        robot->getAngleV("UPPER_TORSO") + changeInX);
        break;

      case MENU_LOWER_TORSO:
        robot->setAngle("LOWER_TORSO", 
                        robot->getAngleH("LOWER_TORSO") + changeInY, 
                        robot->getAngleV("LOWER_TORSO") + changeInX);
        break;

      case MENU_PELVIS:
        robot->setAngle("PELVIS", 
                        robot->getAngleH("PELVIS") + changeInY, 
                        robot->getAngleV("PELVIS") + changeInX);
        break;

      case MENU_LEFT_SHOULDER:
        robot->setAngle("LEFT_SHOULDER", 
                        robot->getAngleH("LEFT_SHOULDER") + changeInY, 
                        robot->getAngleV("LEFT_SHOULDER") + changeInX);
        break;

      case MENU_LEFT_UPPER_ARM:
        robot->setAngle("LEFT_UPPER_ARM", 
                        robot->getAngleH("LEFT_UPPER_ARM") + changeInY, 
                        robot->getAngleV("LEFT_UPPER_ARM") + changeInX);
        break;

      case MENU_LEFT_LOWER_ARM:
        robot->setAngle("LEFT_LOWER_ARM", 
                        robot->getAngleH("LEFT_LOWER_ARM") + changeInY, 
                        robot->getAngleV("LEFT_LOWER_ARM") + changeInX);
        break;

      case MENU_LEFT_HAND:
        robot->setAngle("LEFT_HAND", 
                        robot->getAngleH("LEFT_HAND") + changeInY, 
                        robot->getAngleV("LEFT_HAND") + changeInX);
        break;

      case MENU_RIGHT_SHOULDER:
        robot->setAngle("RIGHT_SHOULDER", 
                        robot->getAngleH("RIGHT_SHOULDER") + changeInY, 
                        robot->getAngleV("RIGHT_SHOULDER") + changeInX);
        break;

      case MENU_RIGHT_UPPER_ARM:
        robot->setAngle("RIGHT_UPPER_ARM", 
                        robot->getAngleH("RIGHT_UPPER_ARM") + changeInY, 
                        robot->getAngleV("RIGHT_UPPER_ARM") + changeInX);
        break;

      case MENU_RIGHT_LOWER_ARM:
        robot->setAngle("RIGHT_LOWER_ARM", 
                        robot->getAngleH("RIGHT_LOWER_ARM") + changeInY, 
                        robot->getAngleV("RIGHT_LOWER_ARM") + changeInX);
        break;

      case MENU_RIGHT_HAND:
        robot->setAngle("RIGHT_HAND", 
                        robot->getAngleH("RIGHT_HAND") + changeInY, 
                        robot->getAngleV("RIGHT_HAND") + changeInX);
        break;

      case MENU_LEFT_UPPER_LEG:
        robot->setAngle("LEFT_UPPER_LEG", 
                        robot->getAngleH("LEFT_UPPER_LEG") + changeInY, 
                        robot->getAngleV("LEFT_UPPER_LEG") + changeInX);
        break;

      case MENU_LEFT_LOWER_LEG:
        robot->setAngle("LEFT_LOWER_LEG", 
                        robot->getAngleH("LEFT_LOWER_LEG") + changeInY, 
                        robot->getAngleV("LEFT_LOWER_LEG") + changeInX);
        break;

      case MENU_LEFT_FOOT:
        robot->setAngle("LEFT_FOOT", 
                        robot->getAngleH("LEFT_FOOT") + changeInY, 
                        robot->getAngleV("LEFT_FOOT") + changeInX);
        break;

      case MENU_RIGHT_UPPER_LEG:
        robot->setAngle("RIGHT_UPPER_LEG", 
                        robot->getAngleH("RIGHT_UPPER_LEG") + changeInY, 
                        robot->getAngleV("RIGHT_UPPER_LEG") + changeInX);
        break;

      case MENU_RIGHT_LOWER_LEG:
        robot->setAngle("RIGHT_LOWER_LEG", 
                        robot->getAngleH("RIGHT_LOWER_LEG") + changeInY, 
                        robot->getAngleV("RIGHT_LOWER_LEG") + changeInX);
        break;

      case MENU_RIGHT_FOOT:
        robot->setAngle("RIGHT_FOOT", 
                        robot->getAngleH("RIGHT_FOOT") + changeInY, 
                        robot->getAngleV("RIGHT_FOOT") + changeInX);
        break;

      default: // Exit on unknown state
        printf("ERROR: Unknown menu state <%i> in motion!\n", currentMode);
        return;
    }

    oldX = x;
    oldY = y;

    glutPostRedisplay();
  }
}

/**
 * Callback used for menu events.
 */
void menuEvent(int id) {
   switch (id) {
    case MENU_NORMAL_MODE:
      printf("Entering normal mode...\n");
      robot->clearSelect();
      break;

    case MENU_ZOOM_MODE:
      printf("Entering zoom mode...\n");
      robot->clearSelect();
      break;

    case MENU_PAN_MODE:
      printf("Entering pan mode...\n");
      robot->clearSelect();
      break;

    case MENU_HEAD:
      printf("Entering head editing...\n");
      robot->setSelected("HEAD");
      break;

    case MENU_NECK:
      printf("Entering neck editing...\n");
      robot->setSelected("NECK");
      break;

    case MENU_UPPER_TORSO:
      printf("Entering upper torso editing...\n");
      robot->setSelected("UPPER_TORSO");
      break;

    case MENU_LOWER_TORSO:
      printf("Entering lower torso editing...\n");
      robot->setSelected("LOWER_TORSO");
      break;

    case MENU_PELVIS:
      printf("Entering pelvis editing...\n");
      robot->setSelected("PELVIS");
      break;

    case MENU_LEFT_SHOULDER:
      printf("Entering left shoulder editing...\n");
      robot->setSelected("LEFT_SHOULDER");
      break;

    case MENU_LEFT_UPPER_ARM:
      printf("Entering left upper arm editing...\n");
      robot->setSelected("LEFT_UPPER_ARM");
      break;

    case MENU_LEFT_LOWER_ARM:
      printf("Entering left lower arm editing...\n");
      robot->setSelected("LEFT_LOWER_ARM");
      break;

    case MENU_LEFT_HAND:
      printf("Entering left hand editing...\n");
      robot->setSelected("LEFT_HAND");
      break;

    case MENU_RIGHT_SHOULDER:
      printf("Entering right shoulder editing...\n");
      robot->setSelected("RIGHT_SHOULDER");
      break;

    case MENU_RIGHT_UPPER_ARM:
      printf("Entering right upper arm editing...\n");
      robot->setSelected("RIGHT_UPPER_ARM");
      break;

    case MENU_RIGHT_LOWER_ARM:
      printf("Entering right lower arm editing...\n");
      robot->setSelected("RIGHT_LOWER_ARM");
      break;

    case MENU_RIGHT_HAND:
      printf("Entering right hand editing...\n");
      robot->setSelected("RIGHT_HAND");
      break;

    case MENU_LEFT_UPPER_LEG:
      printf("Entering left upper leg editing...\n");
      robot->setSelected("LEFT_UPPER_LEG");
      break;

    case MENU_LEFT_LOWER_LEG:
      printf("Entering left lower leg editing...\n");
      robot->setSelected("LEFT_LOWER_LEG");
      break;

    case MENU_LEFT_FOOT:
      printf("Entering left foot editing...\n");
      robot->setSelected("LEFT_FOOT");
      break;

    case MENU_RIGHT_UPPER_LEG:
      printf("Entering right upper leg editing...\n");
      robot->setSelected("RIGHT_UPPER_LEG");
      break;

    case MENU_RIGHT_LOWER_LEG:
      printf("Entering right lower leg editing...\n");
      robot->setSelected("RIGHT_LOWER_LEG");
      break;

    case MENU_RIGHT_FOOT:
      printf("Entering right foot editing...\n");
      robot->setSelected("RIGHT_FOOT");
      break;

    default: // Exit on unknown state
      printf("ERROR: Unknown menu state <%i>\n", id);
      return;
  }

 // Update the mode to reflect the changes
  currentMode = id;
}

/**
 * Callback used for freeing memory when program ends.
 */
void terminate_prog(void) {
  // Deallocate memory for robot
  printf("Deallocating robot...\n");
  delete robot;
  robot = NULL;
}

