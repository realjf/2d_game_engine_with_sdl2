#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <iostream>
#include "game_state.h"

class MenuState : public GameState {
public:
    MenuState();
    virtual ~MenuState() {}
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();

private:
    static void StartGame();
    static void ExitGame();
    static void Settings();
    static void Editor();
};

#endif /* _MENU_STATE_H_ */
