#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "animation/keyframe.h"
#include "animation/animation_clip.h"
#include "camera/camera.h"
#include "robot/robot.h"
#include "light/light.h"
#include "serialize/serialfile.h"
#include "text/text.h"

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

const int MENU_SAVE_POSE       = 22;
const int MENU_LOAD_POSE       = 23;

const int MENU_SAVE_ANIM       = 24;
const int MENU_LOAD_ANIM       = 25;

const float DISTANCE = 50.0f;

const unsigned int DEFAULT_FRAMES_PER_SECOND = 30;
const int MIN_FRAMES = 1;
const int MAX_FRAMES = 120;

const GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat diffuse[] = {0.8f, 0.6f, 0.4f, 1.0f};
const GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat shine = 100.0f;

int buildPopupMenu(void);
void arrowPress(int key, int x, int y);
void keyPress(unsigned char key, int x, int y);
void mouseEvent(int button, int state, int x, int y);
void mouseMoveEvent(int x, int y);
void menuEvent(int id);
void render(void);
void idleEvent(void);
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
AnimationClip aClip;
Camera camera;

// Frames per second
unsigned int framesPerSecond;
int currentTime;
int baseTime;
int frames;
int framesTotal;

// Playback counters
int isPlaying;
int playingForward;
int playingBackward;

void initMaterial(void) {
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
}

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
  glEnable(GL_NORMALIZE);

  //glutReshapeFunc(/* ... */);
  glutSpecialFunc(arrowPress);
  glutKeyboardFunc(keyPress);
  glutMouseFunc(mouseEvent);
  glutMotionFunc(mouseMoveEvent);
  glutDisplayFunc(render);
  glutIdleFunc(idleEvent);

  // Build and attach the menu
  buildPopupMenu();
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // Allocate memory for a new robot
  printf("Allocating new robot...\n");
  robot = new Robot();

  // Add robot initial keyframe to animation clip
  {
    Keyframe k_;
    k_.getKeyframeFromRobot(robot);
    aClip.addKeyframeAtCurrent(k_);
  }

  printf("Setting up the camera...\n");
  camera.setCameraMaxDistance(4.0f);
  //camera.lock();

  // Set default fps
  framesPerSecond = DEFAULT_FRAMES_PER_SECOND;
  isPlaying = 0;
  playingForward = 1;
  playingBackward = 0;
  currentTime = 0;
  baseTime = 0;
  frames = 0;
  framesTotal = 0;

  // Set termination callback
  atexit(terminate_prog);

  // Enable lighting
  setupLight();

  // Setup a global material
  initMaterial();

  // Enable texture
  glEnable(GL_TEXTURE_2D);
  robot->loadTexture("texture/CorrugatedSharp.png");

  // Start the main loop
  glutMainLoop();

  // Exit program
  return 0;
}

/**
 * Locks frames per second based on current lock.
 */
void idleEvent(void) {
    if (isPlaying) {
        int newTime = glutGet(GLUT_ELAPSED_TIME);
        if ((newTime - currentTime) >= (1000.0f / framesPerSecond)) {
            if (playingForward) {
                aClip.incrementFrame(true);
                if (aClip.getCurrentFrameIndex() == aClip.getMaxFrameIndex())
                    isPlaying = 0; 
            }
            if (playingBackward) {
                aClip.decrementFrame(true);
                if (aClip.getCurrentFrameIndex() == 1)
                    isPlaying = 0;
            }
            currentTime = newTime;
            ++frames;
        }

        // If over a second
        if ((newTime - baseTime) >= 1000.0f) {
           currentTime = newTime;
            baseTime = newTime;
            framesTotal = frames;
            frames = 0;
        }
    }

    glutPostRedisplay();
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
  Keyframe k_ = aClip.getCurrentFrame();
  robot->getRobotFromKeyframe(&k_);
  robot->render();

  /* Draw the text */
  glLoadIdentity();
  std::string msg;

  char frame[4];

  // The current frame
  sprintf(frame, "%d", aClip.getCurrentFrameIndex());
  msg = "Current Frame: ";
  msg += frame;
  Text::drawBitmapString(-0.9f, 0.9f, GLUT_BITMAP_8_BY_13, msg);
  
  // The current keyframe
  sprintf(frame, "%d", aClip.getKeyframeIndex());
  msg = "Keyframe: ";
  if (aClip.isKeyframeAtCurrent()) msg += frame;
  Text::drawBitmapString(-0.9f, 0.85f, GLUT_BITMAP_8_BY_13, msg);

  // Actual frames per second
  sprintf(frame, "%d", framesTotal);
  msg = "Frames Per Second: ";
  if (isPlaying) msg += frame;
  Text::drawBitmapString(-0.9f, 0.80f, GLUT_BITMAP_8_BY_13, msg);

  // The requested FPS
  sprintf(frame, "%d", framesPerSecond);
  msg = "Requested FPS: ";
  msg += frame;
  Text::drawBitmapString(-0.9f, -0.9f, GLUT_BITMAP_8_BY_13, msg);

  // Playing status
  if (isPlaying) {
    if (playingForward) msg = "Forward";
    if (playingBackward) msg = "Backward";
  } else {
    msg = "Stopped";
  }  
  Text::drawBitmapString(0.8f, -0.9f, GLUT_BITMAP_8_BY_13, msg);
 

  /* Swap the buffers to display changes */
  glutSwapBuffers();
}

/**
 * Generates and returns the id to the menu to be used.
 */
int buildPopupMenu(void) {
  int menu;
  int observeMenu, poseMenu, animMenu, changeMenu;

  observeMenu = glutCreateMenu(menuEvent);
  glutAddMenuEntry("Enable Normal Mode", MENU_NORMAL_MODE);
  glutAddMenuEntry("Enable Zoom Mode", MENU_ZOOM_MODE);
  glutAddMenuEntry("Enable Pan Mode", MENU_PAN_MODE);

  poseMenu = glutCreateMenu(menuEvent);
  glutAddMenuEntry("Save Pose to File", MENU_SAVE_POSE);
  glutAddMenuEntry("Load Pose from File", MENU_LOAD_POSE);

  animMenu = glutCreateMenu(menuEvent);
  glutAddMenuEntry("Save Animation to File", MENU_SAVE_ANIM);
  glutAddMenuEntry("Load Animation from File", MENU_LOAD_ANIM);

  changeMenu = glutCreateMenu(menuEvent);
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

  /* Create the main menu containing submenus */
  menu = glutCreateMenu(menuEvent);
  glutAddSubMenu("Observe Options", observeMenu);
  glutAddSubMenu("Pose File Options", poseMenu);
  glutAddSubMenu("Animation File Options", animMenu);
  glutAddSubMenu("Change Options", changeMenu);

  return menu;
}

/**
 * Keyboard callback
 */
void arrowPress(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      aClip.decrementFrame(true);
      //camera.panLeft(1);
      break;

    case GLUT_KEY_RIGHT:
      aClip.incrementFrame(false);
      //camera.panRight(1);
      break;

    case GLUT_KEY_UP:
      if (++framesPerSecond > MAX_FRAMES) framesPerSecond = MAX_FRAMES;
      //camera.zoomIn(0.1f);
      break;

    case GLUT_KEY_DOWN:
      if (--framesPerSecond < MIN_FRAMES) framesPerSecond = MIN_FRAMES;
      //camera.zoomOut(0.1f);
      break;
  }
  glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            baseTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
            isPlaying = 1;
            playingForward = 1;
            playingBackward = 0;
            break;

        case 'b':
            baseTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
            isPlaying = 1;
            playingForward = 0;
            playingBackward = 1;
            break;

        case 's':
            baseTime = currentTime = glutGet(GLUT_ELAPSED_TIME);
            isPlaying = 0;
            break;

        case 'd':
            aClip.deleteKeyframeAtCurrent();
            break;

        case 32: // Space stores current frame as keyframe
            Keyframe k_;
            k_.getKeyframeFromRobot(robot);
            aClip.addKeyframeAtCurrent(k_);
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

    // If shift is being held, do something special
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        if (changeInX > 0) {
            aClip.incrementFrame(false);
        } else if (changeInX < 0) {
            aClip.decrementFrame(true);
        }

        oldX = x;
        oldY = y;

        glutPostRedisplay();
        return;
    }

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

    Keyframe k_;
    k_.getKeyframeFromRobot(robot);
    aClip.setFrameAt(aClip.getCurrentFrameIndex(), k_);

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
//      robot->clearSelect();
      break;

    case MENU_ZOOM_MODE:
      printf("Entering zoom mode...\n");
//      robot->clearSelect();
      break;

    case MENU_PAN_MODE:
      printf("Entering pan mode...\n");
//      robot->clearSelect();
      break;

    case MENU_LOAD_POSE: {
      printf("Loading pose from pose.dat...\n");
      Keyframe k;
      SerialFile f("pose.dat", "rb");
      k.readFromFile(f.getPointer());
      f.close();
      aClip.setFrameAt(aClip.getCurrentFrameIndex(), k);
      robot->getRobotFromKeyframe(&k);
      id = MENU_NORMAL_MODE;
      break;
    }

    case MENU_SAVE_POSE: {
      printf("Saving pose from pose.dat...\n");
      Keyframe k;
      k.getKeyframeFromRobot(robot);
      SerialFile f("pose.dat", "wb");
      k.writeToFile(f.getPointer());
      f.close();
      id = MENU_NORMAL_MODE;
      break;
    }

    case MENU_SAVE_ANIM: {
      SerialFile f("anim.dat", "wb");
      aClip.writeToFile(f.getPointer());
      f.close();
      id = MENU_NORMAL_MODE;
      break;
    }

    case MENU_LOAD_ANIM: {
      SerialFile f("anim.dat", "rb");
      aClip.readFromFile(f.getPointer());
      f.close();
      id = MENU_NORMAL_MODE;
      break;
    }

    case MENU_HEAD:
      printf("Entering head editing...\n");
//      robot->setSelected("HEAD");
      break;

    case MENU_NECK:
      printf("Entering neck editing...\n");
//      robot->setSelected("NECK");
      break;

    case MENU_UPPER_TORSO:
      printf("Entering upper torso editing...\n");
//      robot->setSelected("UPPER_TORSO");
      break;

    case MENU_LOWER_TORSO:
      printf("Entering lower torso editing...\n");
//      robot->setSelected("LOWER_TORSO");
      break;

    case MENU_PELVIS:
      printf("Entering pelvis editing...\n");
//      robot->setSelected("PELVIS");
      break;

    case MENU_LEFT_SHOULDER:
      printf("Entering left shoulder editing...\n");
//      robot->setSelected("LEFT_SHOULDER");
      break;

    case MENU_LEFT_UPPER_ARM:
      printf("Entering left upper arm editing...\n");
//      robot->setSelected("LEFT_UPPER_ARM");
      break;

    case MENU_LEFT_LOWER_ARM:
      printf("Entering left lower arm editing...\n");
//      robot->setSelected("LEFT_LOWER_ARM");
      break;

    case MENU_LEFT_HAND:
      printf("Entering left hand editing...\n");
//      robot->setSelected("LEFT_HAND");
      break;

    case MENU_RIGHT_SHOULDER:
      printf("Entering right shoulder editing...\n");
//      robot->setSelected("RIGHT_SHOULDER");
      break;

    case MENU_RIGHT_UPPER_ARM:
      printf("Entering right upper arm editing...\n");
//      robot->setSelected("RIGHT_UPPER_ARM");
      break;

    case MENU_RIGHT_LOWER_ARM:
      printf("Entering right lower arm editing...\n");
//      robot->setSelected("RIGHT_LOWER_ARM");
      break;

    case MENU_RIGHT_HAND:
      printf("Entering right hand editing...\n");
//      robot->setSelected("RIGHT_HAND");
      break;

    case MENU_LEFT_UPPER_LEG:
      printf("Entering left upper leg editing...\n");
//      robot->setSelected("LEFT_UPPER_LEG");
      break;

    case MENU_LEFT_LOWER_LEG:
      printf("Entering left lower leg editing...\n");
//      robot->setSelected("LEFT_LOWER_LEG");
      break;

    case MENU_LEFT_FOOT:
      printf("Entering left foot editing...\n");
//      robot->setSelected("LEFT_FOOT");
      break;

    case MENU_RIGHT_UPPER_LEG:
      printf("Entering right upper leg editing...\n");
//      robot->setSelected("RIGHT_UPPER_LEG");
      break;

    case MENU_RIGHT_LOWER_LEG:
      printf("Entering right lower leg editing...\n");
//      robot->setSelected("RIGHT_LOWER_LEG");
      break;

    case MENU_RIGHT_FOOT:
      printf("Entering right foot editing...\n");
//      robot->setSelected("RIGHT_FOOT");
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

