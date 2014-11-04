#include <map>
#include <stdio.h>
#include "robot.h"

std::map<std::string, VertexBox> body;
std::map<std::string, bool> isSelected;
std::map<std::string, float> hAngles;
std::map<std::string, float> vAngles;


/**
 * Initializes the robot.
 */
Robot::Robot(void) {
  selectedBody = "";
  setupBody();
  setupAngles();
}

/**
 * Destroys the robot.
 */
Robot::~Robot(void) {

}

/**
 * Sets up the body of the robot.
 */
void Robot::setupBody(void) {
  body.insert(std::make_pair("HEAD", makeBoxList(
    -0.5f,  0.5f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Top-left
     0.5f,  0.5f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Top-right
    -0.5f, -0.5f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Bottom-left
     0.5f, -0.5f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Bottom-right
    -0.5f,  0.5f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Top-left
     0.5f,  0.5f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Top-right
    -0.5f, -0.5f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f), // Bottom-left
     0.5f, -0.5f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)  // Bottom-right
  )));
  isSelected.insert(std::make_pair("HEAD", false));
  body.insert(std::make_pair("NECK", makeBoxList(
    -0.25f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.25f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.25f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.25f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.25f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.25f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.25f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.25f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("NECK", false));
  body.insert(std::make_pair("UPPER_TORSO", makeBoxList(
    -0.5f,  1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("UPPER_TORSO", false));
  body.insert(std::make_pair("LOWER_TORSO", makeBoxList(
    -0.5f,  1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -1.0f,  1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -1.0f, -1.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LOWER_TORSO", false));
  body.insert(std::make_pair("PELVIS", makeBoxList(
    -0.5f,  0.5f,  1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -1.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("PELVIS", false));
  body.insert(std::make_pair("LEFT_SHOULDER", makeBoxList(
    -0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_SHOULDER", false));
  body.insert(std::make_pair("RIGHT_SHOULDER", makeBoxList(
    -0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_SHOULDER", false));
  body.insert(std::make_pair("LEFT_UPPER_ARM", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_UPPER_ARM", false));
  body.insert(std::make_pair("RIGHT_UPPER_ARM", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_UPPER_ARM", false));
  body.insert(std::make_pair("LEFT_LOWER_ARM", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_LOWER_ARM", false));
  body.insert(std::make_pair("RIGHT_LOWER_ARM", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_LOWER_ARM", false));
  body.insert(std::make_pair("LEFT_HAND", makeBoxList(
    -0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_HAND", false));
  body.insert(std::make_pair("RIGHT_HAND", makeBoxList(
    -0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_HAND", false));
  body.insert(std::make_pair("LEFT_UPPER_LEG", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_UPPER_LEG", false));
  body.insert(std::make_pair("RIGHT_UPPER_LEG", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_UPPER_LEG", false));
  body.insert(std::make_pair("LEFT_LOWER_LEG", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_LOWER_LEG", false));
  body.insert(std::make_pair("RIGHT_LOWER_LEG", makeBoxList(
    -0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f,  0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.5f, -0.25f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_LOWER_LEG", false));
  body.insert(std::make_pair("LEFT_FOOT", makeBoxList(
    -0.5f,  0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("LEFT_FOOT", false));
  body.insert(std::make_pair("RIGHT_FOOT", makeBoxList(
    -0.5f,  0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f,  0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f,  0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f,  0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.5f, -0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.5f, -0.25f, -0.5f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("RIGHT_FOOT", false));
  body.insert(std::make_pair("FLOOR", makeBoxList(
    -0.0f,  0.0f,  0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.0f,  0.0f,  0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.0f, -0.0f,  0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.0f, -0.0f,  0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.0f,  0.0f, -0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.0f,  0.0f, -0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
    -0.0f, -0.0f, -0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f),
     0.0f, -0.0f, -0.0f, Color4f(1.0f, 0.0f, 0.0f, 1.0f)
  )));
  isSelected.insert(std::make_pair("FLOOR", false));
}

/**
 * Sets up all angles used by the robot.
 */
void Robot::setupAngles(void) {
  vAngles.insert(std::make_pair("HEAD", 0.0f));
  vAngles.insert(std::make_pair("NECK", 0.0f));
  vAngles.insert(std::make_pair("UPPER_TORSO", 0.0f));
  vAngles.insert(std::make_pair("LOWER_TORSO", 0.0f));
  vAngles.insert(std::make_pair("PELVIS", 0.0f));
  vAngles.insert(std::make_pair("LEFT_SHOULDER", 0.0f));
  vAngles.insert(std::make_pair("LEFT_UPPER_ARM", 0.0f));
  vAngles.insert(std::make_pair("LEFT_LOWER_ARM", 0.0f));
  vAngles.insert(std::make_pair("LEFT_HAND", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_SHOULDER", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_UPPER_ARM", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_LOWER_ARM", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_HAND", 0.0f));
  vAngles.insert(std::make_pair("LEFT_UPPER_LEG", 0.0f));
  vAngles.insert(std::make_pair("LEFT_LOWER_LEG", 0.0f));
  vAngles.insert(std::make_pair("LEFT_FOOT", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_UPPER_LEG", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_LOWER_LEG", 0.0f));
  vAngles.insert(std::make_pair("RIGHT_FOOT", 0.0f));

  hAngles.insert(std::make_pair("HEAD", 0.0f));
  hAngles.insert(std::make_pair("NECK", 0.0f));
  hAngles.insert(std::make_pair("UPPER_TORSO", 0.0f));
  hAngles.insert(std::make_pair("LOWER_TORSO", 0.0f));
  hAngles.insert(std::make_pair("PELVIS", 0.0f));
  hAngles.insert(std::make_pair("LEFT_SHOULDER", 0.0f));
  hAngles.insert(std::make_pair("LEFT_UPPER_ARM", 0.0f));
  hAngles.insert(std::make_pair("LEFT_LOWER_ARM", 0.0f));
  hAngles.insert(std::make_pair("LEFT_HAND", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_SHOULDER", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_UPPER_ARM", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_LOWER_ARM", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_HAND", 0.0f));
  hAngles.insert(std::make_pair("LEFT_UPPER_LEG", 0.0f));
  hAngles.insert(std::make_pair("LEFT_LOWER_LEG", 0.0f));
  hAngles.insert(std::make_pair("LEFT_FOOT", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_UPPER_LEG", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_LOWER_LEG", 0.0f));
  hAngles.insert(std::make_pair("RIGHT_FOOT", 0.0f));
}

/**
 * Renders the robot onto the screen.
 */
void Robot::render(void) {
  // Draw the floor
  glColor3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(0.0f, -6.75f, 0.0f);
    glBegin(GL_QUADS);
      glVertex3f(-10.0f, 0.0f, -10.0f);
      glVertex3f(10.0f, 0.0f, -10.0f);
      glVertex3f(10.0f, 0.0f, 10.0f);
      glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
  glPopMatrix();

  // Render the base upper torso
  rotatePart("UPPER_TORSO");
  renderBoxf(body["UPPER_TORSO"], isSelected["UPPER_TORSO"], true);

  // Render lower body
  glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    rotatePart("LOWER_TORSO");
    renderBoxf(body["LOWER_TORSO"], isSelected["LOWER_TORSO"], true);
    glPushMatrix();
      glTranslatef(0.0f, -1.5f, 0.0f);
      rotatePart("PELVIS");
      renderBoxf(body["PELVIS"], isSelected["PELVIS"], true);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, -1.0f);
        rotatePart("LEFT_UPPER_LEG");
        renderBoxf(body["LEFT_UPPER_LEG"], isSelected["LEFT_UPPER_LEG"], true);
        glTranslatef(0.0f, -1.0f, 0.0f);
        glPushMatrix();
          rotatePart("LEFT_LOWER_LEG");
          renderBoxf(body["LEFT_LOWER_LEG"], isSelected["LEFT_LOWER_LEG"], true);
          glTranslatef(0.0f, -0.75f, 0.0f);
          glPushMatrix();
            rotatePart("LEFT_FOOT");
            renderBoxf(body["LEFT_FOOT"], isSelected["LEFT_FOOT"], true);
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 1.0f);
        rotatePart("RIGHT_UPPER_LEG");
        renderBoxf(body["RIGHT_UPPER_LEG"], isSelected["RIGHT_UPPER_LEG"], true);
        glTranslatef(0.0f, -1.0f, 0.0f);
        glPushMatrix();
          rotatePart("RIGHT_LOWER_LEG");
          renderBoxf(body["RIGHT_LOWER_LEG"], isSelected["RIGHT_LOWER_LEG"], true);
          glTranslatef(0.0f, -0.75f, 0.0f);
          glPushMatrix();
            rotatePart("RIGHT_FOOT");
            renderBoxf(body["RIGHT_FOOT"], isSelected["RIGHT_FOOT"], true);
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();  

  // Render left arm
  glPushMatrix();
    glTranslatef(0.0f, 0.75f, -1.75f);
    rotatePart("LEFT_SHOULDER");
    renderBoxf(body["LEFT_SHOULDER"], isSelected["LEFT_SHOULDER"], true);
    glPushMatrix();
      glTranslatef(0.0f, -0.75f, 0.0f);
      rotatePart("LEFT_UPPER_ARM");
      renderBoxf(body["LEFT_UPPER_ARM"], isSelected["LEFT_UPPER_ARM"], true);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        rotatePart("LEFT_LOWER_ARM");
        renderBoxf(body["LEFT_LOWER_ARM"], isSelected["LEFT_LOWER_ARM"], true);
        glPushMatrix();
          glTranslatef(0.0f, -0.75f, 0.0f);
          rotatePart("LEFT_HAND");
          renderBoxf(body["LEFT_HAND"], isSelected["LEFT_HAND"], true);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  // Render right arm
  glPushMatrix();
    glTranslatef(0.0f, 0.75f, 1.75f);
    rotatePart("RIGHT_SHOULDER");
    renderBoxf(body["RIGHT_SHOULDER"], isSelected["RIGHT_SHOULDER"], true);
    glPushMatrix();
      glTranslatef(0.0f, -0.75f, 0.0f);
      rotatePart("RIGHT_UPPER_ARM");
      renderBoxf(body["RIGHT_UPPER_ARM"], isSelected["RIGHT_UPPER_ARM"], true);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        rotatePart("RIGHT_LOWER_ARM");
        renderBoxf(body["RIGHT_LOWER_ARM"], isSelected["RIGHT_LOWER_ARM"], true);
        glPushMatrix();
          glTranslatef(0.0f, -0.75f, 0.0f);
          rotatePart("RIGHT_HAND");
          renderBoxf(body["RIGHT_HAND"], isSelected["RIGHT_HAND"], true);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  // Render neck and head
  glPushMatrix();
    glTranslatef(0.0f, 1.25f, 0.0f);
    rotatePart("NECK");
    renderBoxf(body["NECK"], isSelected["NECK"], true);
    glPushMatrix();
      glTranslatef(0.0f, 0.75f, 0.0f);
      rotatePart("HEAD");
      renderBoxf(body["HEAD"], isSelected["HEAD"], true);
    glPopMatrix();
  glPopMatrix();
}

/**
 * Sets the angles for the specified name.
 * angleName: The name of the angle
 * newAngleH: The new horizontal angle value
 * newAngleV: The new vertical angle value
 */
void Robot::setAngle(std::string angleName,
                     const float newAngleH, const float newAngleV) {
  // Exit if the name is not found
  if (hAngles.find(angleName) == hAngles.end()) return;
  if (vAngles.find(angleName) == vAngles.end()) return;

  // Set the new angle
  hAngles[angleName] = newAngleH;
  vAngles[angleName] = newAngleV;
}

float Robot::getAngleH(std::string angleName) {
  if (hAngles.find(angleName) == hAngles.end())
    return 0.0f;

  return hAngles[angleName];
}

float Robot::getAngleV(std::string angleName) {
  if (vAngles.find(angleName) == vAngles.end())
    return 0.0f;

  return vAngles[angleName];
}

/**
 * Renders a box using v0-v3 as one side and v4-v7 as the other
 * side and connecting the sides together to form the other
 * four sides.
 * 
 * v0 connects to v1, v2, and v4.
 * v1 connects to v0, v3, and v5.
 * v2 connects to v0, v3, and v6.
 * v3 connects to v1, v2, and v7.
 *  
 * v4 connects to v5, v6, and v0.
 * v5 connects to v4, v7, and v1.
 * v6 connects to v4, v7, and v2.
 * v7 connects to v5, v6, and v3.
 */
void Robot::renderBoxf(VertexBox vBox, bool highlight, bool outline) {
  /* Make the first side v0-v3 */
  /* TopLeft:     V0           */
  /* TopRight:    V1           */
  /* BottomRight: V3           */
  /* BottomLeft:  V2           */
  glBegin(GL_QUADS);
    setColor(vBox.v0.color.invertIfTrue(highlight));
    setVertex(vBox.v0);
    setColor(vBox.v1.color.invertIfTrue(highlight));
    setVertex(vBox.v1);
    setColor(vBox.v3.color.invertIfTrue(highlight));
    setVertex(vBox.v3);
    setColor(vBox.v2.color.invertIfTrue(highlight));
    setVertex(vBox.v2);
  glEnd();

  /* Make the opposite side v4-v7 */
  /* TopLeft:     V4              */
  /* TopRight:    V5              */
  /* BottomRight: V7              */
  /* BottomLeft:  V6              */
  glBegin(GL_QUADS);
    setColor(vBox.v4.color.invertIfTrue(highlight));
    setVertex(vBox.v4);
    setColor(vBox.v5.color.invertIfTrue(highlight));
    setVertex(vBox.v5);
    setColor(vBox.v7.color.invertIfTrue(highlight));
    setVertex(vBox.v7);
    setColor(vBox.v6.color.invertIfTrue(highlight));
    setVertex(vBox.v6);
  glEnd();

  /* Render sides inbetween */
  glBegin(GL_QUAD_STRIP);
    setColor(vBox.v0.color.invertIfTrue(highlight));
    setVertex(vBox.v0);
    setColor(vBox.v4.color.invertIfTrue(highlight));
    setVertex(vBox.v4);
    setColor(vBox.v1.color.invertIfTrue(highlight));
    setVertex(vBox.v1);
    setColor(vBox.v5.color.invertIfTrue(highlight));
    setVertex(vBox.v5);
    setColor(vBox.v3.color.invertIfTrue(highlight));
    setVertex(vBox.v3);
    setColor(vBox.v7.color.invertIfTrue(highlight));
    setVertex(vBox.v7);
    setColor(vBox.v2.color.invertIfTrue(highlight));
    setVertex(vBox.v2);
    setColor(vBox.v6.color.invertIfTrue(highlight));
    setVertex(vBox.v6);
    setColor(vBox.v0.color.invertIfTrue(highlight));
    setVertex(vBox.v0);
    setColor(vBox.v4.color.invertIfTrue(highlight));
    setVertex(vBox.v4);
  glEnd();

  if (outline) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
      setVertex(vBox.v0);
      setVertex(vBox.v1);
      setVertex(vBox.v3);
      setVertex(vBox.v2);
      setVertex(vBox.v0);
      setVertex(vBox.v4);
      setVertex(vBox.v5);
      setVertex(vBox.v7);
      setVertex(vBox.v6);
      setVertex(vBox.v4);
      setVertex(vBox.v5);
      setVertex(vBox.v1);
      setVertex(vBox.v3);
      setVertex(vBox.v7);
      setVertex(vBox.v6);
      setVertex(vBox.v2);
    glEnd();
  }
}

/**
 * Sets the color according to the color provided.
 *
 * c: The color to use
 */
inline void Robot::setColor(Color4f c) {
  glColor4f(c.red, c.green, c.blue, c.alpha);
}

/**
 * Sets the new vertex to be used.
 *
 * v: The vertex to use
 */
inline void Robot::setVertex(Vertex3f v) {
  glVertex3f(v.x, v.y, v.z);
}

/**
 * Rotates part by angles specified for part.
 */
inline void Robot::rotatePart(std::string name) {
  glRotatef(hAngles[name], 0.0f, 0.0f, 1.0f);
  glRotatef(vAngles[name], 0.0f, 1.0f, 0.0f);
}

/**
 * Creates a series of eight Vertex3f structures in an array
 * that contain the provided points and colors.
 */
VertexBox Robot::makeBoxList(float v0x, float v0y, float v0z, Color4f v0c,
                             float v1x, float v1y, float v1z, Color4f v1c,
                             float v2x, float v2y, float v2z, Color4f v2c,
                             float v3x, float v3y, float v3z, Color4f v3c,
                             float v4x, float v4y, float v4z, Color4f v4c,
                             float v5x, float v5y, float v5z, Color4f v5c,
                             float v6x, float v6y, float v6z, Color4f v6c,
                             float v7x, float v7y, float v7z, Color4f v7c) {
    VertexBox vBox(
      Vertex3f(v0x, v0y, v0z, v0c),
      Vertex3f(v1x, v1y, v1z, v1c),
      Vertex3f(v2x, v2y, v2z, v2c),
      Vertex3f(v3x, v3y, v3z, v3c),
      Vertex3f(v4x, v4y, v4z, v4c),
      Vertex3f(v5x, v5y, v5z, v5c),
      Vertex3f(v6x, v6y, v6z, v6c),
      Vertex3f(v7x, v7y, v7z, v7c)
    );

  return vBox;
}

void Robot::setSelected(std::string bodyName) {
  // Deselect the currently-selected body
  if (!selectedBody.empty())
    isSelected[selectedBody] = false;

  // Select the new body
  isSelected[bodyName] = true;
  selectedBody = bodyName;
}

std::string Robot::getSelected(void) {
  return selectedBody;
}

void Robot::clearSelect(void) {
  if (!selectedBody.empty())
    isSelected[selectedBody] = false;
  selectedBody = "";
}

