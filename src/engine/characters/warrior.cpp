#include "warrior.h"
#include "graphics/texture_manager.h"
#include <SDL.h>
#include "inputs/input.h"

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Scale);
}

void Warrior::Update(float dt) {
    m_Animation->SetProps("viking_idle", 0, 2, 300, m_Direction == FORWARD ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    m_RigidBody->UnSetForce();

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_RigidBody->ApplyForceX(5 * BACKWARD);
        m_Animation->SetProps("viking_run", 0, 5, 100, SDL_FLIP_HORIZONTAL);
        m_Direction = BACKWARD;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_RigidBody->ApplyForceX(5 * FORWARD);
        m_Animation->SetProps("viking_run", 0, 5, 100);
        m_Direction = FORWARD;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_Animation->SetProps("viking_jump", 0, 5, 150);
    }

    m_RigidBody->Update(dt);

    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    // m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

    m_Animation->SetSpriteFrame((SDL_GetTicks() / m_Animation->GetAnimSpeed()) % (m_Animation->GetFrameCount()));

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;
    m_Animation->Update(false);
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Clean();
}

Warrior::Warrior(Properties *props) : Character(props) {
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 5, 100, SDL_FLIP_HORIZONTAL);
}
