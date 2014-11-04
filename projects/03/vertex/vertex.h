#include <GL/gl.h>
#include <stdio.h>

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
    private:
       GLfloat x_, y_, z_,    // Vertex Coordinates
               nx_, ny_, nz_, // Normal Coordinates
               tx_, ty_;      // Texture Coordinates

    public:
        Vertex(void);
        Vertex(GLfloat, GLfloat, GLfloat,
               GLfloat, GLfloat, GLfloat,
               GLfloat, GLfloat);
        Vertex(const GLfloat[]);

        ~Vertex(void);

        void toFloatArray(GLfloat[]);
        void fromFloatArray(const GLfloat[]);

        void writeToFile(FILE*);
        void readFromFile(FILE*);
};

#endif

