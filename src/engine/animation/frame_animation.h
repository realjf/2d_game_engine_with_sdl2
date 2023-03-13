#ifndef _FRAME_ANIMATION_H_
#define _FRAME_ANIMATION_H_

#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <tinyxml.h>
#include "physics/transform.h"
#include "sequence_animation.h"

#define ANIMATION_FOLDER "assets/animations/"

class FrameAnimation {
public:
    FrameAnimation(std::string file, Transform *objTf);
    ~FrameAnimation();

    void Draw();
    void Update();
    bool Parse(std::string source);
    bool SetCurrentSeq(std::string seqID);

private:
    Uint8 m_CurrentFrame;
    Sequence *m_CurrentSeq;
    Transform *m_ObjectTransform;
    std::map<std::string, Sequence *> m_SeqMap;
};

#endif /* _FRAME_ANIMATION_H_ */
