
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

#ifndef TEXT_H
#define TEXT_H

class Text {
    private:

    public:
        static void drawBitmapString(float x, float y, void* font, std::string str) {
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos3f(x, y, -1.0f);
            for (int i = 0; i < str.size(); ++i) {
                glutBitmapCharacter(font, str[i]);
            }
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
        }
};

#endif

