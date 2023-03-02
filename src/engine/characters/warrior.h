#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "character.h"
#include "animation/animation.h"
#include "physics/rigid_body.h"

class Warrior : public Character {
public:
    Warrior(Properties *props);
    virtual ~Warrior() {}

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();

private:
    // int m_Row, m_Frame, m_FrameCount, m_RowCount;
    // int m_AnimSpeed;

    Animation *m_Animation;
    RigidBody *m_RigidBody;
    int m_Direction;
};

#endif /* _WARRIOR_H_ */
