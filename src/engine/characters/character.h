#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object/game_object.h"

class Character : public GameObject {
public:
    Character(Properties *props) : GameObject(props) {}

    virtual ~Character() {}

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

protected:
    std::string m_Name;
};

#endif /* _CHARACTER_H_ */
