#include "warrior.h"
#include "graphics/texture_manager.h"
#include <SDL.h>
#include "inputs/input.h"
#include "collision/collision_manager.h"
#include "camera/camera.h"

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Scale);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt) {
    m_RigidBody->UnSetForce();
    m_Flip = SDL_FLIP_NONE;
    m_Velocity = 0;
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        // m_RigidBody->ApplyForceX(5 * BACKWARD);
        m_Direction = BACKWARD;
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_Velocity.X = 5 * m_Direction;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        // m_RigidBody->ApplyForceX(5 * FORWARD);
        m_Direction = FORWARD;
        m_Flip = SDL_FLIP_NONE;
        m_Velocity.X = 5 * m_Direction;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        // m_RigidBody->ApplyForceY(5 * UPWARD);
        m_Direction = UPWARD;
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_Velocity.Y = 5 * m_Direction;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        // m_RigidBody->ApplyForceY(5 * DOWNWARD);
        m_Direction = DOWNWARD;
        m_Flip = SDL_FLIP_NONE;
        m_Velocity.Y = 5 * m_Direction;
    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        // m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        // m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    } else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->Translate(m_Velocity);
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    // if (CollisionManager::GetInstance()->MapCollision(m_Collider->Get())) {
    //     m_Transform->X = m_LastSafePosition.X;
    // }

    // m_RigidBody->Update(dt);
    // m_LastSafePosition.Y = m_Transform->Y;
    // m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    // m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    // if (CollisionManager::GetInstance()->MapCollision(m_Collider->Get())) {
    //     m_IsGrounded = true;
    //     m_Transform->Y = m_LastSafePosition.Y;
    // } else {
    //     m_IsGrounded = false;
    // }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    AnimationState();

    m_Animation->SetSpriteFrame((SDL_GetTicks() / m_Animation->GetAnimSpeed()) % (m_Animation->GetFrameCount()));
    m_Animation->Update(false);
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Drop(m_TextureID);
}

void Warrior::AnimationState() {
    m_Animation->SetProps("viking_idle", 0, 2, 300, m_Flip);

    if (m_IsRunning) {
        m_Animation->SetProps("viking_run", 0, 5, 100, m_Flip);
    }

    if (m_IsJumping) {
        m_Animation->SetProps("viking_jump", 0, 5, 150, m_Flip);
    }
}

Warrior::Warrior(Properties *props) : Character(props) {
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 5, 100, SDL_FLIP_HORIZONTAL);

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking = false;
    m_IsCrouching = false;

    m_Flip = SDL_FLIP_NONE;
    m_AttackTime = ATTACK_TIME;
}
