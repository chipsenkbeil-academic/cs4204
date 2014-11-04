/**
 * The header file implementing the camera to be used.
 * Written by Robert "Chip" Senkbeil
 */

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  private:
    bool locked;
    float panX;
    int rotateXAngle;
    int rotateYAngle;
    float cameraDistance;
    float cameraZoom;
    float targetX;
    float targetY;
    float targetZ;

  public:
    /**
     * The default constructor for the camera class.
     */
    Camera(void);

    /**
     * The default destructor for the camera class.
     */
    ~Camera(void);

    /**
     * Updates the camera in OpenGL using gluLookAt.
     */
    void update(void);

    /**
     * Sets the camera's maximum distance from its target.
     */
    void setCameraMaxDistance(float distance);

    /**
     * Sets the camera's zoom.
     */
    void setCameraZoom(float zoom);

    /**
     * Sets the camera's rotation angle in relation to its target.
     */
    void setCameraRotateAngle(int angleX, int angleY);

    /**
     * Sets the camera's target.
     */
    void setCameraTarget(float x, float y, float z);

    /**
     * Pans the camera left.
     */
    void panLeft(float distance);

    /**
     * Pans the camera right.
     */
    void panRight(float distance);

    /**
     * Rotates the camera left.
     */
    void rotateLeft(int degrees);

    /**
     * Rotates the camera right.
     */
    void rotateRight(int degrees);

    /**
     * Rotates the camera up.
     */
    void rotateUp(int degrees);

    /**
     * Rotates the camera down.
     */
    void rotateDown(int degrees);

    /**
     * Zoom in the specified amount.
     */
    void zoomIn(float zoom);

    /**
     * Zoom out the specified amount.
     */
    void zoomOut(float zoom);

    /**
     * Locks the camera such that no movement occurs.
     */
    void lock(void);

    /**
     * Unlocks the camera such that movement occurs.
     */
    void unlock(void);
};

#endif

