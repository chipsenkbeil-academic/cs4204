#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "../camera/camera.h"

#define PI 3.14159265

/**
 * Initializes the camera.
 */
Camera::Camera(void) {
  locked = false;
  panX = 0.0f;
  rotateXAngle = 0;
  rotateYAngle = 0;
  cameraDistance = 0.0f;
  cameraZoom = 1.0f;
  targetX = 0.0f;
  targetY = 0.0f;
  targetZ = 0.0f;
}

/**
 * Destroys the camera.
 */
Camera::~Camera(void) {

}

void Camera::update(void) {
  glTranslatef(panX, 0.0f, 0.0f);
  gluLookAt(
    targetX + cameraDistance / cameraZoom * cos(rotateXAngle * PI / 180.0f),
    targetY + cameraDistance / cameraZoom * sin(rotateYAngle * PI / 180.0f),
    targetZ + cameraDistance / cameraZoom * sin(rotateXAngle * PI / 180.0f),
    targetX, targetY, targetZ,
    0.0f, 1.0f, 0.0f
  );
}

void Camera::setCameraMaxDistance(float distance) {
  if (!locked) cameraDistance = distance;
}

void Camera::setCameraRotateAngle(int angleX, int angleY) {
  if (!locked) {
    rotateXAngle = angleX;
    rotateYAngle = angleY;
  }
}

void Camera::setCameraTarget(float x, float y, float z) {
  if (!locked) {
    targetX = x;
    targetY = y;
    targetZ = z;
  }
}

void Camera::panLeft(float distance) {
  if (!locked) panX -= distance;
}

void Camera::panRight(float distance) {
  if (!locked) panX -= distance;
}

void Camera::rotateLeft(int degrees) {
  if (!locked) rotateXAngle -= degrees;
  if (rotateXAngle <= -360.0f) rotateXAngle = -360.0f; 
}

void Camera::rotateRight(int degrees) {
  if (!locked) rotateXAngle += degrees;
  if (rotateXAngle >= 360.0f) rotateXAngle = 360.0f;
}

void Camera::rotateUp(int degrees) {
  if (!locked) rotateYAngle -= degrees;
  if (rotateYAngle <= -360.0f) rotateYAngle = -360.0f;
}

void Camera::rotateDown(int degrees) {
  if (!locked) rotateYAngle += degrees;
  if (rotateYAngle >= 360.0f) rotateYAngle = 360.0f;
}

void Camera::zoomIn(float zoom) {
  if (!locked) cameraZoom += zoom;
}

void Camera::zoomOut(float zoom) {
  if (!locked) cameraZoom -= zoom;
}

void Camera::lock(void) {
  locked = true;
}

void Camera::unlock(void) {
  locked = false;
}
