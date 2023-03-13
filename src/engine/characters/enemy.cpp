#include "enemy.h"
#include "factory/object_factory.h"

static Registrar<Enemy> registrar("BOSS");

Enemy::Enemy(Transform *tf) : Character(tf) {
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5);
    m_Collider = new Collider();

    m_Animation = new SequenceAnimation();
    m_Animation->Parse("assets/data/animation.xml");
    m_Animation->SetCurrentSeq("boss_idle");
}

void Enemy::Draw() {
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Transform->ScaleX, m_Transform->ScaleY, m_Transform->Flip);

    m_Collider->Draw();
}

void Enemy::Clean() {
}

void Enemy::Update(float dt) {
    m_RigidBody->Update(dt);
    m_Transform->X += m_RigidBody->GetPosition().X;

    m_Animation->Update(dt);
    if (m_Animation->IsEnded()) {
        m_Animation->SetCurrentSeq("boss_idle");
        m_Animation->SetRepeat(false);
    }
}
