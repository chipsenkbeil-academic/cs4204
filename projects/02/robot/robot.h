/**
 * The header file implementing the robot to be drawn.
 * Written by Robert "Chip" Senkbeil
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <GL/gl.h>
#include <string>

class Robot {
  private:
    std::string selectedBody;

    void setupBody(void);
    void setupAngles(void);

    /**
     * Renders a box using the provided vertices and scales it based on the
     * provided width, height, and depth.
     */
    void renderBoxf(float* vertices, float width, float height, float depth);

    /**
     * Rotates the part with the specified name by its
     * set angles of rotation.
     */
    inline void rotatePart(std::string name);
  public:

    /**
     * The default constructor for the robot class.
     */
    Robot(void);

    /**
     * The default destructor for the robot class.
     */
    ~Robot(void);

    /**
     * Renders the robot onto the screen.
     */
    void render(void);

    /**
     * Sets the angle with the specified name.
     * angleName: The name of the angle
     * newAngleH: The new horizontal angle value
     * newAngleV: The new vertical angle value
     */
    void setAngle(std::string angleName, 
                  const float newAngleH, const float newAngleV);

    /**
     * Returns the horizontal angle associated with the specified name.
     */
    float getAngleH(std::string angleName);

    /**
     * Returns the vertical angle associated with the specified name.
     */
    float getAngleV(std::string angleName);

    /**
     * Loads the texture onto the robot.
     */
    void loadTexture(const char* file);
};

#endif
