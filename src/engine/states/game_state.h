#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

class GameState {
public:
    virtual bool Init() = 0;
    virtual bool Exit() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif /* _GAME_STATE_H_ */
