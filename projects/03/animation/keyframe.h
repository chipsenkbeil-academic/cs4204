
#include <list>
#include "../robot/robot.h"
#include "../vertex/vertex.h"

#ifndef KEYFRAME_H
#define KEYFRAME_H

class Robot;

/*
 * Stores all vertices at the specified point as well as all angles, light,
 * and textures associated with the frame.
 */
class Keyframe {
    private:
        std::list<Vertex> vList; // Vertex list
        std::list<float> fhList; // Horizontal angle list
        std::list<float> fvList; // Vertical angle list

    public:
        Keyframe(void);
        ~Keyframe(void);

        void getKeyframeFromRobot(Robot*);

        std::list<Vertex> getVertices(void);
        void addVertex(Vertex);

        std::list<float> getHorizontalAngles(void);
        std::list<float> getVerticalAngles(void);
        void addAngle(float, float);
        void addAngleH(float);
        void addAngleV(float);

        void writeToFile(FILE*);
        void readFromFile(FILE*);
};

#endif

