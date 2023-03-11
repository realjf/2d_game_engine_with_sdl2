#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "character.h"
#include "animation/animation.h"
#include "physics/rigid_body.h"
#include "physics/collider.h"

#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f;

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
    Collider *m_Collider;
    Vector2D m_LastSafePosition;
    bool m_IsGrounded;
    bool m_IsJumping;
    float m_JumpTime;
    float m_JumpForce;
    Vector2D m_Velocity;
    int m_Direction;
};

#endif /* _WARRIOR_H_ */
