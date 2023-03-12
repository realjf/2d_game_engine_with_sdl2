#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <vector>
#include "game_state.h"

class StateManager {
public:
    void PopState();
    void PushState(GameState *state);
    void ChangeState(GameState *state);

private:
    std::vector<GameState *> m_States;
};

#endif /* _STATE_MANAGER_H_ */
