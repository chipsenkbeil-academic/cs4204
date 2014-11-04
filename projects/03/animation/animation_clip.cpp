
#include "animation_clip.h"

AnimationClip::AnimationClip(void) :
    currentFrame(1)
{
    // Insert a blank first keyframe
    Keyframe k;
    addKeyframeAtCurrent(k);
}

AnimationClip::~AnimationClip(void) {

}

void AnimationClip::addKeyframeAt(int index, Keyframe k) {
    KeyframeWithIndex k_;

    k_.k = k;
    k_.index = index;

    // If empty, just push back
    if (kList.empty()) {
        kList.push_back(k_);
        return;
    }

    // Overwrite or insert
    int prevIndex = -1;
    std::list<KeyframeWithIndex>::iterator kIt;
    for (kIt = kList.begin(); kIt != kList.end(); ++kIt) {
        if (index == kIt->index) {
            kList.insert(kIt, k_);
            kList.erase(kIt);
            break;
        } else if (index > prevIndex && index < kIt->index) {
            kList.insert(kIt, k_);
            break;
        } else {
            if (++kIt == kList.end()) {
                kList.push_back(k_);
                break;
            }
            --kIt;
        }
        prevIndex = kIt->index;
    }

    // Generate new frame set
    updateInterpolation();
}

void AnimationClip::addKeyframeAtCurrent(Keyframe k) {
    addKeyframeAt(currentFrame, k);
}

/**
 * Sets frame in frame list, not keyframe list.
 */
void AnimationClip::setFrameAt(int index, Keyframe k) {
    std::list<Keyframe>::iterator fIt;
    int i;
    for (i = 1, fIt = fList.begin(); fIt != fList.end(); ++i, ++fIt) {
        if (index == i) {
            fList.insert(fIt, k);
            fList.erase(fIt);
            break;
        }
    }
}

void AnimationClip::deleteKeyframeAt(int index) {
    std::list<KeyframeWithIndex>::iterator kIt;
    for (kIt = kList.begin(); kIt != kList.end(); ++kIt) {
        if (index == kIt->index) {
            kList.erase(kIt);
            updateInterpolation();
            return;
        }
    }
}

void AnimationClip::deleteKeyframeAtCurrent(void) {
    deleteKeyframeAt(currentFrame);
}

int AnimationClip::isKeyframeAt(int index) {
    std::list<KeyframeWithIndex>::iterator kIt;
    for (kIt = kList.begin(); kIt != kList.end(); ++kIt) {
        if (index == kIt->index) {
            return 1;
        }
    }
    return 0;
}

int AnimationClip::isKeyframeAtCurrent(void) {
    return isKeyframeAt(currentFrame);
}

int AnimationClip::getKeyframeIndex(void) {
    std::list<KeyframeWithIndex>::iterator kIt;
    int i;
    for (i = 1, kIt = kList.begin(); kIt != kList.end(); ++i, ++kIt) {
        if (currentFrame == kIt->index) {
            return i;
        }
    }
    return -1;
   
}

int AnimationClip::getMaxFrameIndex(void) {
    return kList.back().index;
}

int AnimationClip::getCurrentFrameIndex(void) {
    return currentFrame;
}

void AnimationClip::incrementFrame(int lock) {
    if (++currentFrame > kList.back().index && lock)
        currentFrame = kList.back().index;
}

void AnimationClip::decrementFrame(int lock) {
    if (--currentFrame < 1 && lock)
        currentFrame = 1;
}

Keyframe AnimationClip::getFrameAt(int index) {
    std::list<Keyframe>::iterator fIt;
    int i;
    for (i = 1, fIt = fList.begin();
         fIt != fList.end();
         ++i, ++fIt) {
        if (i == index) {
            return *fIt;
        }
    }

    Keyframe k_;
    return k_;
}

Keyframe AnimationClip::getCurrentFrame(void) {
    return getFrameAt(currentFrame);
}

void AnimationClip::updateInterpolation(void) {
    fList.clear();
    // Exit if there are no keyframes
    if (kList.empty()) return;

    std::list<KeyframeWithIndex>::iterator kIt;
    for (kIt = kList.begin(); kIt != kList.end(); ++kIt) {
        fList.push_back(kIt->k);

        // Exit if last keyframe
        if (++kIt == kList.end()) return; --kIt;

        std::list<float> hAngles_start = kIt->k.getHorizontalAngles();
        std::list<float> vAngles_start = kIt->k.getVerticalAngles();

        ++kIt;
        std::list<float> hAngles_end = kIt->k.getHorizontalAngles();
        std::list<float> vAngles_end = kIt->k.getVerticalAngles();
        --kIt;

        int startingIndex = kIt->index;
        int endingIndex = (++kIt)->index; --kIt;
        int framesAfter = endingIndex - startingIndex - 1;

        for (int i = 0; i < framesAfter; ++i) {
            Keyframe k_;
            std::list<float>::iterator hIt_start;
            std::list<float>::iterator hIt_end;
            for (hIt_start = hAngles_start.begin(), hIt_end = hAngles_end.begin(); 
                 hIt_start != hAngles_start.end(), hIt_end != hAngles_end.end(); 
                 ++hIt_start, ++hIt_end) {
                k_.addAngleH(calculateInterpolate(*hIt_start, *hIt_end, startingIndex, endingIndex, i + startingIndex + 1));
            }
            std::list<float>::iterator vIt_start;
            std::list<float>::iterator vIt_end;
            for (vIt_start = vAngles_start.begin(), vIt_end = vAngles_end.begin(); 
                 vIt_start != vAngles_start.end(), vIt_end != vAngles_end.end(); 
                 ++vIt_start, ++vIt_end) {
                k_.addAngleV(calculateInterpolate(*vIt_start, *vIt_end, startingIndex, endingIndex, i + startingIndex + 1));
            }

            std::list<Vertex> vList = kIt->k.getVertices();
            std::list<Vertex>::iterator vIt;
            for (vIt = vList.begin(); vIt != vList.end(); ++vIt) {
                k_.addVertex(*vIt);
            }

            fList.push_back(k_);
        }
    }

}

void AnimationClip::writeToFile(FILE* f) {
    std::list<KeyframeWithIndex>::iterator kIt;
    int totalKeyframes = kList.size();
    fwrite(&totalKeyframes, sizeof(int), 1, f);
    for (kIt = kList.begin(); kIt != kList.end(); ++kIt) {
        int index = kIt->index;
        fwrite(&index, sizeof(int), 1, f);
        kIt->k.writeToFile(f);
    }
}

void AnimationClip::readFromFile(FILE* f) {
    kList.clear();
    int totalKeyframes;
    fread(&totalKeyframes, sizeof(int), 1, f);
    for (int i = 0; i < totalKeyframes; ++i) {
        int index; KeyframeWithIndex k_;
        fread(&index, sizeof(int), 1, f);
        k_.k.readFromFile(f);
        k_.index = index;
        kList.push_back(k_);
    }

    updateInterpolation();
}

/*
 * a0: Angle 0, starting angle
 * a1: Angle 1, ending angle
 * f0: Frame 0, starting frame
 * f1: Frame 1, ending frame
 * cf: Current Frame
 */
float AnimationClip::calculateInterpolate(float a0, float a1, int f0, int f1, int cf) {
    float percentLeft = ((float) (f1 - cf)) / ((float) f1 - f0);

//fprintf(stderr, "a0:%f|a1:%f|f0:%d|f1:%d|cf:%d\n", a0, a1, f0, f1, cf);
//fprintf(stderr, "Percent Left: %f\n", percentLeft);
//fprintf(stderr, "Angle: %f\n", (a0 * (percentLeft) + a1 * (1.0f - percentLeft)));

    return (a0 * (percentLeft) + a1 * (1.0f - percentLeft));
}

