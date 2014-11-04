
#include <list>
#include <stdio.h>
#include "keyframe.h"

#ifndef ANIMATIONCLIP_H
#define ANIMATIONCLIP_H

/*
 * Contains a keyframe that may or may not
 * be a real keyframe or could just be a normal
 * frame and also contains the index of the frame.
 */
struct KeyframeWithIndex {
    Keyframe k;
    int index;
};

class AnimationClip {
    private:
        std::list<KeyframeWithIndex> kList;
        std::list<Keyframe> fList;
        int currentFrame;
        float calculateInterpolate(float, float, int, int, int);

    public:
        AnimationClip(void);
        ~AnimationClip(void);

        void addKeyframeAt(int, Keyframe);
        void addKeyframeAtCurrent(Keyframe);

        void setFrameAt(int, Keyframe);

        void deleteKeyframeAt(int);
        void deleteKeyframeAtCurrent(void);

        int isKeyframeAt(int);
        int isKeyframeAtCurrent(void);

        int getKeyframeIndex(void);
        int getCurrentFrameIndex(void);
        int getMaxFrameIndex(void);
        void incrementFrame(int);
        void decrementFrame(int);

        Keyframe getFrameAt(int);
        Keyframe getCurrentFrame(void);

        void updateInterpolation(void); 

        void writeToFile(FILE*);
        void readFromFile(FILE*);
};

#endif

