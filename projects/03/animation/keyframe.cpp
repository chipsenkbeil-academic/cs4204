#include <stdio.h>
#include "keyframe.h"

Keyframe::Keyframe(void) {
    // Do nothing
}

Keyframe::~Keyframe(void) {
    // Do nothing
}

void Keyframe::getKeyframeFromRobot(Robot* r) {
    vList.clear();
    fhList.clear();
    fvList.clear();

    std::list<Vertex> rVertices = r->getVertices();
    std::list<Vertex>::iterator vIt;
    for (vIt = rVertices.begin(); vIt != rVertices.end(); ++vIt) {
        addVertex(*vIt);
    }

    addAngle(r->getAngleH("HEAD"), r->getAngleV("HEAD"));
    addAngle(r->getAngleH("NECK"), r->getAngleV("NECK"));
    addAngle(r->getAngleH("UPPER_TORSO"), r->getAngleV("UPPER_TORSO"));
    addAngle(r->getAngleH("LOWER_TORSO"), r->getAngleV("LOWER_TORSO"));
    addAngle(r->getAngleH("PELVIS"), r->getAngleV("PELVIS"));
    addAngle(r->getAngleH("LEFT_SHOULDER"), r->getAngleV("LEFT_SHOULDER"));
    addAngle(r->getAngleH("LEFT_UPPER_ARM"), r->getAngleV("LEFT_UPPER_ARM"));
    addAngle(r->getAngleH("LEFT_LOWER_ARM"), r->getAngleV("LEFT_LOWER_ARM"));
    addAngle(r->getAngleH("LEFT_HAND"), r->getAngleV("LEFT_HAND"));
    addAngle(r->getAngleH("RIGHT_SHOULDER"), r->getAngleV("RIGHT_SHOULDER"));
    addAngle(r->getAngleH("RIGHT_UPPER_ARM"), r->getAngleV("RIGHT_UPPER_ARM"));
    addAngle(r->getAngleH("RIGHT_LOWER_ARM"), r->getAngleV("RIGHT_LOWER_ARM"));
    addAngle(r->getAngleH("RIGHT_HAND"), r->getAngleV("RIGHT_HAND"));
    addAngle(r->getAngleH("LEFT_UPPER_LEG"), r->getAngleV("LEFT_UPPER_LEG"));
    addAngle(r->getAngleH("LEFT_LOWER_LEG"), r->getAngleV("LEFT_LOWER_LEG"));
    addAngle(r->getAngleH("LEFT_FOOT"), r->getAngleV("LEFT_FOOT"));
    addAngle(r->getAngleH("RIGHT_UPPER_LEG"), r->getAngleV("RIGHT_UPPER_LEG"));
    addAngle(r->getAngleH("RIGHT_LOWER_LEG"), r->getAngleV("RIGHT_LOWER_LEG"));
    addAngle(r->getAngleH("RIGHT_FOOT"), r->getAngleV("RIGHT_FOOT"));
}

std::list<Vertex> Keyframe::getVertices(void) {
    return vList;
}

void Keyframe::addVertex(Vertex v) {
    vList.push_back(v);
}

std::list<float> Keyframe::getHorizontalAngles(void) {
    return fhList;
}

std::list<float> Keyframe::getVerticalAngles(void) {
    return fvList;
}

void Keyframe::addAngle(float h, float v) {
    fhList.push_back(h);
    fvList.push_back(v);
}

void Keyframe::addAngleH(float h) {
    fhList.push_back(h);
}

void Keyframe::addAngleV(float v) {
    fvList.push_back(v);
}

void Keyframe::writeToFile(FILE* f) {
    int list_sizes[3];
    list_sizes[0] = vList.size();
    list_sizes[1] = fhList.size();
    list_sizes[2] = fvList.size();

    fwrite(list_sizes, sizeof(int), 3, f);

    std::list<Vertex>::iterator vIt;
    for (vIt = vList.begin(); vIt != vList.end(); ++vIt) {
        vIt->writeToFile(f);
    }

    std::list<float>::iterator fhIt;
    for (fhIt = fhList.begin(); fhIt != fhList.end(); ++fhIt) {
        float a = *fhIt;
        fwrite(&a, sizeof(float), 1, f);
    }

    std::list<float>::iterator fvIt;
    for (fvIt = fvList.begin(); fvIt != fvList.end(); ++fvIt) {
        float a = *fvIt;
        fwrite(&a, sizeof(float), 1, f);
    }
}

void Keyframe::readFromFile(FILE* f) {
    vList.clear();
    fhList.clear();
    fvList.clear();

    int list_sizes[3];

    fread(list_sizes, sizeof(int), 3, f);

    for (int i = 0; i < list_sizes[0]; ++i) {
        Vertex v;
        v.readFromFile(f);
        vList.push_back(v);
    }

    for (int i = 0; i < list_sizes[1]; ++i) {
        float h;
        fread(&h, sizeof(float), 1, f);
        fhList.push_back(h);
    }

    for (int i = 0; i < list_sizes[2]; ++i) {
        float v;
        fread(&v, sizeof(float), 1, f);
        fvList.push_back(v);
    }
}

