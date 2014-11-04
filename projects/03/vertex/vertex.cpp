#include "vertex.h"

Vertex::Vertex(void) {
    x_ = 0; y_ = 0; z_ = 0;
    nx_ = 0; ny_ = 0; nz_ = 0;
    tx_ = 0; ty_ = 0;
}

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z,
               GLfloat nx, GLfloat ny, GLfloat nz,
               GLfloat tx, GLfloat ty) :
               x_(x), y_(y), z_(z), 
               nx_(nx), ny_(ny), nz_(nz),
               tx_(tx), ty_(ty) {}

Vertex::Vertex(const GLfloat fArray[]) {
    fromFloatArray(fArray);
}

Vertex::~Vertex(void) {
    // Do nothing
}

void Vertex::toFloatArray(GLfloat fArray[]) {
    fArray[0] = x_; fArray[1] = y_; fArray[2] = z_;
    fArray[3] = nx_; fArray[4] = ny_; fArray[5] = nz_;
    fArray[6] = tx_; fArray[7] = ty_;
}

void Vertex::fromFloatArray(const GLfloat fArray[]) {
    x_ = fArray[0]; y_ = fArray[1]; z_ = fArray[2];
    nx_ = fArray[3]; ny_ = fArray[4]; nz_ = fArray[5];
    tx_ = fArray[6]; ty_ = fArray[7];
}

void Vertex::writeToFile(FILE* f) {
    GLfloat fArray[8];
    toFloatArray(fArray);
    fwrite(fArray, sizeof(GLfloat), 8, f);
}

void Vertex::readFromFile(FILE* f) {
    GLfloat fArray[8];
    fread(fArray, sizeof(GLfloat), 8, f);
    fromFloatArray(fArray);
}

