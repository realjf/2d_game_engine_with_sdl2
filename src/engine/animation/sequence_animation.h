#ifndef _SEQUENCE_ANIMATION_H_
#define _SEQUENCE_ANIMATION_H_

#include <map>
#include <vector>
#include <string>
#include <SDL.h>
#include "animation.h"

class Sequence {
public:
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureIDs;
};

class SequenceAnnotation : public Animation {
public:
    SequenceAnnotation(bool repeat);

    virtual void Update(float dt);
    void Parse(std::string source);
    void SetCurrentSeq(std::string seqID);
    void SetRepeat(bool repeat) { m_Repeat = repeat; }
    void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    Sequence m_CurrentSeq;
    std::map<std::string, Sequence> m_Sequences;
};

#endif /* _SEQUENCE_ANIMATION_H_ */
