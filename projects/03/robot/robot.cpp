#include <map>
#include <stdio.h>
#include "../lib_soil/SOIL.h"
#include "robot.h"

static const int CUBE_VERTICES = 24;

int texture;
std::map<std::string, float> bodyX;
std::map<std::string, float> bodyY;
std::map<std::string, float> bodyZ;
std::map<std::string, float> hAngles;
std::map<std::string, float> vAngles;

// For textures
float texCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};

// Used to provide normals for lighting
float normals[] = {
    // From z of 1
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
/*
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
*/

    // From -x
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    // From x
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // From z of -1
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f

};

// Used to draw a cube that will be scaled
float vertices[] = {
     // Front
    -1.0f,  1.0f,  1.0f, // Front-Top-Left
     1.0f,  1.0f,  1.0f, // Front-Top-Right
     1.0f, -1.0f,  1.0f, // Front-Bottom-Right
    -1.0f, -1.0f,  1.0f, // Front-Bottom-Left

     // Left side
    -1.0f,  1.0f, -1.0f, // Back-Top-left
    -1.0f, -1.0f, -1.0f, // Back-Bottom-left
    -1.0f, -1.0f,  1.0f, // Front-Bottom-Left
    -1.0f,  1.0f,  1.0f, // Front-Top-Left

     // Right side
     1.0f,  1.0f, -1.0f, // Back-Top-right
     1.0f, -1.0f, -1.0f, // Back-Bottom-right
     1.0f, -1.0f,  1.0f, // Front-Bottom-Right
     1.0f,  1.0f,  1.0f, // Front-Top-Right

     // Back
    -1.0f,  1.0f, -1.0f, // Back-Top-left
     1.0f,  1.0f, -1.0f, // Back-Top-right
     1.0f, -1.0f, -1.0f, // Back-Bottom-right
    -1.0f, -1.0f, -1.0f, // Back-Bottom-left

     // Top
    -1.0f,  1.0f,  1.0f, // Front-Top-Left
     1.0f,  1.0f,  1.0f, // Front-Top-Right
     1.0f,  1.0f, -1.0f, // Back-Top-right
    -1.0f,  1.0f, -1.0f, // Back-Top-left
 
     // Bottom
    -1.0f, -1.0f,  1.0f, // Front-Bottom-Left
     1.0f, -1.0f,  1.0f, // Front-Bottom-Right
     1.0f, -1.0f, -1.0f, // Back-Bottom-right
    -1.0f, -1.0f, -1.0f  // Back-Bottom-left
};

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
 * Sets up the scaling values of the 1.0x1.0x1.0 cube used in the glDrawArrays.
 */
void Robot::setupBody(void) {
  bodyX.insert(std::make_pair("HEAD", 0.5f));
  bodyX.insert(std::make_pair("NECK", 0.25f));
  bodyX.insert(std::make_pair("UPPER_TORSO", 0.5f));
  bodyX.insert(std::make_pair("LOWER_TORSO", 0.5f));
  bodyX.insert(std::make_pair("PELVIS", 0.5f));
  bodyX.insert(std::make_pair("LEFT_SHOULDER", 0.5f));
  bodyX.insert(std::make_pair("LEFT_UPPER_ARM", 0.5f));
  bodyX.insert(std::make_pair("LEFT_LOWER_ARM", 0.5f));
  bodyX.insert(std::make_pair("LEFT_HAND", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_SHOULDER", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_UPPER_ARM", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_LOWER_ARM", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_HAND", 0.5f));
  bodyX.insert(std::make_pair("LEFT_UPPER_LEG", 0.5f));
  bodyX.insert(std::make_pair("LEFT_LOWER_LEG", 0.5f));
  bodyX.insert(std::make_pair("LEFT_FOOT", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_UPPER_LEG", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_LOWER_LEG", 0.5f));
  bodyX.insert(std::make_pair("RIGHT_FOOT", 0.5f));

  bodyY.insert(std::make_pair("HEAD", 0.5f));
  bodyY.insert(std::make_pair("NECK", 0.25f));
  bodyY.insert(std::make_pair("UPPER_TORSO", 1.0f));
  bodyY.insert(std::make_pair("LOWER_TORSO", 1.0f));
  bodyY.insert(std::make_pair("PELVIS", 0.5f));
  bodyY.insert(std::make_pair("LEFT_SHOULDER", 0.25f));
  bodyY.insert(std::make_pair("LEFT_UPPER_ARM", 0.5f));
  bodyY.insert(std::make_pair("LEFT_LOWER_ARM", 0.5f));
  bodyY.insert(std::make_pair("LEFT_HAND", 0.25f));
  bodyY.insert(std::make_pair("RIGHT_SHOULDER", 0.25f));
  bodyY.insert(std::make_pair("RIGHT_UPPER_ARM", 0.5f));
  bodyY.insert(std::make_pair("RIGHT_LOWER_ARM", 0.5f));
  bodyY.insert(std::make_pair("RIGHT_HAND", 0.25f));
  bodyY.insert(std::make_pair("LEFT_UPPER_LEG", 0.5f));
  bodyY.insert(std::make_pair("LEFT_LOWER_LEG", 0.5f));
  bodyY.insert(std::make_pair("LEFT_FOOT", 0.25f));
  bodyY.insert(std::make_pair("RIGHT_UPPER_LEG", 0.5f));
  bodyY.insert(std::make_pair("RIGHT_LOWER_LEG", 0.5f));
  bodyY.insert(std::make_pair("RIGHT_FOOT", 0.25f));

  bodyZ.insert(std::make_pair("HEAD", 0.5f));
  bodyZ.insert(std::make_pair("NECK", 0.25f));
  bodyZ.insert(std::make_pair("UPPER_TORSO", 1.5f));
  bodyZ.insert(std::make_pair("LOWER_TORSO", 1.5f));
  bodyZ.insert(std::make_pair("PELVIS", 1.0f));
  bodyZ.insert(std::make_pair("LEFT_SHOULDER", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_UPPER_ARM", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_LOWER_ARM", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_HAND", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_SHOULDER", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_UPPER_ARM", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_LOWER_ARM", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_HAND", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_UPPER_LEG", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_LOWER_LEG", 0.25f));
  bodyZ.insert(std::make_pair("LEFT_FOOT", 0.5f));
  bodyZ.insert(std::make_pair("RIGHT_UPPER_LEG", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_LOWER_LEG", 0.25f));
  bodyZ.insert(std::make_pair("RIGHT_FOOT", 0.5f));
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
  renderBoxf(vertices, bodyX["UPPER_TORSO"], bodyY["UPPER_TORSO"], bodyZ["UPPER_TORSO"]);

  // Render lower body
  glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    rotatePart("LOWER_TORSO");
    renderBoxf(vertices, bodyX["LOWER_TORSO"], bodyY["LOWER_TORSO"], bodyZ["LOWER_TORSO"]);
    glPushMatrix();
      glTranslatef(0.0f, -1.5f, 0.0f);
      rotatePart("PELVIS");
      renderBoxf(vertices, bodyX["PELVIS"], bodyY["PELVIS"], bodyZ["PELVIS"]);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, -1.0f);
        rotatePart("LEFT_UPPER_LEG");
        renderBoxf(vertices, bodyX["LEFT_UPPER_LEG"], bodyY["LEFT_UPPER_LEG"], bodyZ["LEFT_UPPER_LEG"]);
        glTranslatef(0.0f, -1.0f, 0.0f);
        glPushMatrix();
          rotatePart("LEFT_LOWER_LEG");
          renderBoxf(vertices, bodyX["LEFT_LOWER_LEG"], bodyY["LEFT_LOWER_LEG"], bodyZ["LEFT_LOWER_LEG"]);
          glTranslatef(0.0f, -0.75f, 0.0f);
          glPushMatrix();
            rotatePart("LEFT_FOOT");
            renderBoxf(vertices, bodyX["LEFT_FOOT"], bodyY["LEFT_FOOT"], bodyZ["LEFT_FOOT"]);
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 1.0f);
        rotatePart("RIGHT_UPPER_LEG");
        renderBoxf(vertices, bodyX["RIGHT_UPPER_LEG"], bodyY["RIGHT_UPPER_LEG"], bodyZ["RIGHT_UPPER_LEG"]);
        glTranslatef(0.0f, -1.0f, 0.0f);
        glPushMatrix();
          rotatePart("RIGHT_LOWER_LEG");
          renderBoxf(vertices, bodyX["RIGHT_LOWER_LEG"], bodyY["RIGHT_LOWER_LEG"], bodyZ["RIGHT_LOWER_LEG"]);
          glTranslatef(0.0f, -0.75f, 0.0f);
          glPushMatrix();
            rotatePart("RIGHT_FOOT");
            renderBoxf(vertices, bodyX["RIGHT_FOOT"], bodyY["RIGHT_FOOT"], bodyZ["RIGHT_FOOT"]);
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();  

  // Render left arm
  glPushMatrix();
    glTranslatef(0.0f, 0.75f, -1.75f);
    rotatePart("LEFT_SHOULDER");
    renderBoxf(vertices, bodyX["LEFT_SHOULDER"], bodyY["LEFT_SHOULDER"], bodyZ["LEFT_SHOULDER"]);
    glPushMatrix();
      glTranslatef(0.0f, -0.75f, 0.0f);
      rotatePart("LEFT_UPPER_ARM");
      renderBoxf(vertices, bodyX["LEFT_UPPER_ARM"], bodyY["LEFT_UPPER_ARM"], bodyZ["LEFT_UPPER_ARM"]);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        rotatePart("LEFT_LOWER_ARM");
        renderBoxf(vertices, bodyX["LEFT_LOWER_ARM"], bodyY["LEFT_LOWER_ARM"], bodyZ["LEFT_LOWER_ARM"]);
        glPushMatrix();
          glTranslatef(0.0f, -0.75f, 0.0f);
          rotatePart("LEFT_HAND");
          renderBoxf(vertices, bodyX["LEFT_HAND"], bodyY["LEFT_HAND"], bodyZ["LEFT_HAND"]);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  // Render right arm
  glPushMatrix();
    glTranslatef(0.0f, 0.75f, 1.75f);
    rotatePart("RIGHT_SHOULDER");
    renderBoxf(vertices, bodyX["RIGHT_SHOULDER"], bodyY["RIGHT_SHOULDER"], bodyZ["RIGHT_SHOULDER"]);
    glPushMatrix();
      glTranslatef(0.0f, -0.75f, 0.0f);
      rotatePart("RIGHT_UPPER_ARM");
      renderBoxf(vertices, bodyX["RIGHT_UPPER_ARM"], bodyY["RIGHT_UPPER_ARM"], bodyZ["RIGHT_UPPER_ARM"]);
      glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        rotatePart("RIGHT_LOWER_ARM");
        renderBoxf(vertices, bodyX["RIGHT_LOWER_ARM"], bodyY["RIGHT_LOWER_ARM"], bodyZ["RIGHT_LOWER_ARM"]);
        glPushMatrix();
          glTranslatef(0.0f, -0.75f, 0.0f);
          rotatePart("RIGHT_HAND");
          renderBoxf(vertices, bodyX["RIGHT_HAND"], bodyY["RIGHT_HAND"], bodyZ["RIGHT_HAND"]);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  // Render neck and head
  glPushMatrix();
    glTranslatef(0.0f, 1.25f, 0.0f);
    rotatePart("NECK");
    renderBoxf(vertices, bodyX["NECK"], bodyY["NECK"], bodyZ["NECK"]);
    glPushMatrix();
      glTranslatef(0.0f, 0.75f, 0.0f);
      rotatePart("HEAD");
      renderBoxf(vertices, bodyX["HEAD"], bodyY["HEAD"], bodyZ["HEAD"]);
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
 * Renders a box with the provided set of vertices and scales it to the
 * provided width, height, and depth.
 *
 * vertices: The vertices of the box
 * width: The scale width (x)
 * height: The scale height (y)
 * depth: The scale depth (z)
 */
void Robot::renderBoxf(float* vertices, float width, float height, float depth) {
  glPushMatrix(); 
    glScalef(width, height, depth);
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normals);

    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glPopMatrix();
}

/**
 * Rotates part by angles specified for part.
 */
inline void Robot::rotatePart(std::string name) {
  glRotatef(hAngles[name], 0.0f, 0.0f, 1.0f);
  glRotatef(vAngles[name], 0.0f, 1.0f, 0.0f);
}

void Robot::loadTexture(const char* fileName) {
  texture = SOIL_load_OGL_texture(
    fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
  );

  if (texture == 0)
    return;

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return;
}

std::list<Vertex> Robot::getVertices(void) {
    std::list<Vertex> vList;
    for (int i = 0; i < CUBE_VERTICES; ++i) {
        Vertex v(vertices[3*i], vertices[3*i + 1], vertices[3*i + 2],
                 normals[3*i], normals[3*i + 1], normals[3*i + 2],
                 texCoords[2*i], texCoords[2*i + 1]);
        vList.push_back(v);
    }

    return vList;
}

void Robot::getRobotFromKeyframe(Keyframe* k) {
    std::list<Vertex> vList = k->getVertices();
    std::list<float> fhList = k->getHorizontalAngles();
    std::list<float> fvList = k->getVerticalAngles();

    int i;

    std::list<Vertex>::iterator vIt;
    for (i = 0, vIt = vList.begin(); vIt != vList.end(); ++i, ++vIt) {
        GLfloat v[8];
        vIt->toFloatArray(v);
        vertices[3*i] = v[0];
        vertices[3*i + 1] = v[1];
        vertices[3*i + 2] = v[2];
        normals[3*i] = v[3];
        normals[3*i + 1] = v[4];
        normals[3*i + 2] = v[5];
        texCoords[2*i] = v[6];
        texCoords[2*i + 1] = v[7];
    }

    std::string aNames[] = {
        "HEAD", "NECK", "UPPER_TORSO", "LOWER_TORSO", "PELVIS",
        "LEFT_SHOULDER", "LEFT_UPPER_ARM", "LEFT_LOWER_ARM", "LEFT_HAND",
        "RIGHT_SHOULDER", "RIGHT_UPPER_ARM", "RIGHT_LOWER_ARM", "RIGHT_HAND",
        "LEFT_UPPER_LEG", "LEFT_LOWER_LEG", "LEFT_FOOT",
        "RIGHT_UPPER_LEG", "RIGHT_LOWER_LEG", "RIGHT_FOOT"
    };

    std::list<float>::iterator fhIt;
    for (i = 0, fhIt = fhList.begin(); fhIt != fhList.end(); ++i, ++fhIt) {
        hAngles[aNames[i]] = *fhIt;
    }

    std::list<float>::iterator fvIt;
    for (i = 0, fvIt = fvList.begin(); fvIt != fvList.end(); ++i, ++fvIt) {
        vAngles[aNames[i]] = *fvIt;
    }
}

