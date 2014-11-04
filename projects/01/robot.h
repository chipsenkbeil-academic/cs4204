/**
 * The header file implementing the robot to be drawn.
 * Written by Robert "Chip" Senkbeil
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <GL/gl.h>
#include <string>

struct Color4f {
  float red;
  float green;
  float blue;
  float alpha;

  // Returns an inverted color if true, otherwise returns normal color
  Color4f invertIfTrue(bool value) {
    if (value)
      return invert();
    else {
      return copy();
    }
  };

  // Copies the color and returns the copy
  Color4f copy(void) {
    Color4f copyColor;
    copyColor.red = red;
    copyColor.green = green;
    copyColor.blue = blue;
    copyColor.alpha = alpha;
    return copyColor;
  };

  // Inverts the colors (not alpha)
  Color4f invert(void) {
    Color4f invertedColor;
    invertedColor.red = 1.0f - red;
    invertedColor.green = 1.0f - green;
    invertedColor.blue = 1.0f - blue;
    invertedColor.alpha = alpha;
    return invertedColor;
  };

  // Default constructor
  Color4f() {}

  // Copy constructor
  Color4f(const Color4f& c)
    : red(c.red), green(c.green), blue(c.blue), alpha(c.alpha) {}

  // Optional constructor for type
  Color4f(float r, float g, float b, float a)
    : red(r), green(g), blue(b), alpha(a) {}
};

struct Vertex3f {
  float x;
  float y;
  float z;
  Color4f color;

  // Default constructor
  Vertex3f() {}

  // Copy constructor
  Vertex3f(const Vertex3f& v)
    : x(v.x), y(v.y), z(v.z), color(v.color) {}

  // Optional constructor for type
  Vertex3f(float p1, float p2, float p3, Color4f c)
    : x(p1), y(p2), z(p3), color(c) {}
};

struct VertexBox {
  Vertex3f v0;
  Vertex3f v1;
  Vertex3f v2;
  Vertex3f v3;
  Vertex3f v4;
  Vertex3f v5;
  Vertex3f v6;
  Vertex3f v7;

  // Default constructor
  VertexBox() {}

  // Copy constructor
  VertexBox(const VertexBox& vBox)
    : v0(vBox.v0), v1(vBox.v1), v2(vBox.v2), v3(vBox.v3), v4(vBox.v4),
      v5(vBox.v5), v6(vBox.v6), v7(vBox.v7) {}

  // Optional constructor for type
  VertexBox(Vertex3f a0, Vertex3f a1, Vertex3f a2, Vertex3f a3,
            Vertex3f a4, Vertex3f a5, Vertex3f a6, Vertex3f a7)
    : v0(a0), v1(a1), v2(a2), v3(a3), v4(a4), v5(a5), v6(a6), v7(a7) {}
};

class Robot {
  private:
    std::string selectedBody;

    void setupBody(void);
    void setupAngles(void);

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
    void renderBoxf(VertexBox vBox, bool highlight, bool outline);

    /**
     * Creates a series of eight Vertex3f structures in an array
     * that contain the provided points and colors.
     */
    VertexBox makeBoxList(float v0x, float v0y, float v0z, Color4f v0c,
                          float v1x, float v1y, float v1z, Color4f v1c,
                          float v2x, float v2y, float v2z, Color4f v2c,
                          float v3x, float v3y, float v3z, Color4f v3c,
                          float v4x, float v4y, float v4z, Color4f v4c,
                          float v5x, float v5y, float v5z, Color4f v5c,
                          float v6x, float v6y, float v6z, Color4f v6c,
                          float v7x, float v7y, float v7z, Color4f v7c);

    /**
     * Sets the new color to be used by the vertex with the color provided.
     *
     * c: The color to be used
     */
    inline void setColor(Color4f c);

    /**
     * Sets the new vertex to be used.
     *
     * v: The vertex to use
     */
    inline void setVertex(Vertex3f v);

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
     * Sets the body part with the name provided as the currently-selected
     * piece to be altered with future actions.
     */
    void setSelected(std::string bodyName);

    /**
     * Returns the name of the currently-selected body part.
     */
    std::string getSelected(void);

    /**
     * Clears any selection.
     */
    void clearSelect(void);
};

#endif
