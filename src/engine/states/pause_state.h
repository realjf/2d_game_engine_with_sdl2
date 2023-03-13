#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include "game_state.h"

class PauseState : GameState {
public:
    PauseState() {}
    ~PauseState() {}
    
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();
};

#endif /* _PAUSE_STATE_H_ */
