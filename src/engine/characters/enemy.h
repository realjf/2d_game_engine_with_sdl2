#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"
#include "physics/collider.h"
#include "physics/rigid_body.h"
#include "animation/sequence_animation.h"
#include "animation/sprite_animation.h"

class Enemy : public Character {
public:
    Enemy(Transform *tf);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

private:
    Collider *m_Collider;
    RigidBody *m_RigidBody;
    SequenceAnimation *m_Animation;
    Vector2D m_LastSafePosition;
};

#endif /* _ENEMY_H_ */
