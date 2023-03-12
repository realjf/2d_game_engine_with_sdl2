#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <vector>
#include "game_state.h"

class StateManager {
public:
    void PopState();
    void PushState(GameState *state);
    void ChangeState(GameState *state);
    void Clean();

    void Update();
    void Render();

private:
    bool m_Completed;
    std::vector<GameState *> m_States;
};

#endif /* _STATE_MANAGER_H_ */
