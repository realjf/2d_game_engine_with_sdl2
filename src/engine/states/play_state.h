#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include <iostream>
#include <vector>
#include "game_state.h"
#include "maps/game_map.h"
#include "object/game_object.h"
#include "timer/timer.h"
#include "camera/camera.h"
#include "inputs/input.h"
#include "parser/parser.h"
#include "maps/tile_layer.h"
#include "graphics/texture_manager.h"
#include "factory/object_factory.h"
#include "maps/image_layer.h"

class PlayState : public GameState {
public:
    PlayState();
    virtual ~PlayState() {}
    void Events();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();
    inline TileMap *GetMap() { return m_Map; }

private:
    static void OpenMenu();
    static void PauseGame();

private:
    TileMap *m_Map;
    std::vector<ImageLayer *> m_ParalaxBg;
    std::vector<GameObject *> m_GameObjects;
};

#endif /* _PLAY_STATE_H_ */
