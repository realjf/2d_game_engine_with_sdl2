#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "character.h"
#include "animation/sprite_animation.h"
#include "physics/rigid_body.h"
#include "physics/collider.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

#define ATTACK_TIME 20.0f

#define PLAYER_SPEED 10

class Warrior : public Character {
public:
    Warrior(Transform *tf);
    virtual ~Warrior() {}

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();
    void AnimationState();

private:
    // int m_Row, m_Frame, m_FrameCount, m_RowCount;
    // int m_AnimSpeed;

    SpriteAnimation *m_Animation;
    RigidBody *m_RigidBody;
    Collider *m_Collider;
    Vector2D m_LastSafePosition;
    bool m_IsGrounded;
    bool m_IsJumping;
    bool m_IsRunning;
    bool m_IsAttacking;
    bool m_IsCrouching;
    bool m_IsFalling;

    float m_JumpTime;
    float m_JumpForce;
    float m_AttackTime;

    SDL_RendererFlip m_Flip;

    Vector2D m_Velocity;
    int m_Direction;
};

#endif /* _WARRIOR_H_ */
