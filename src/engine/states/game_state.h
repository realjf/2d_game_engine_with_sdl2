#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <SDL.h>

class GameState {
public:
    virtual ~GameState() {}
    virtual bool Init() = 0;
    virtual bool Exit() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    SDL_Renderer *m_Ctxt;
};

#endif /* _GAME_STATE_H_ */
