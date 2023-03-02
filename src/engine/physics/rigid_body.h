#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include "math/vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class RigidBody {
public:
    RigidBody() {
        m_Mass = UNI_MASS;
        m_Gravity = GRAVITY;
    }
    virtual ~RigidBody() {}

    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetGravity(float gravity) { m_Gravity = gravity; }

    // Force
    inline void ApplyForce(Vector2D force) { m_Force = force; }
    inline void ApplyForceX(float forceX) { m_Force.X = forceX; }
    inline void ApplyForceY(float forceY) { m_Force.Y = forceY; }
    inline void UnSetForce() { m_Force = Vector2D(0, 0); }

    // Friction
    inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
    inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }

    // Getters
    inline float GetMass() { return m_Mass; }
    inline Vector2D GetPosition() { return m_Position; }
    inline Vector2D GetVelocity() { return m_Velocity; }
    inline Vector2D GetAcceleration() { return m_Accelaration; }

    void Update(float dt) {
        m_Accelaration.X = (m_Force.X + m_Friction.X) / m_Mass;
        m_Accelaration.Y = m_Gravity + m_Force.Y / m_Mass;
        m_Velocity = m_Accelaration * dt;
        m_Position = m_Velocity * dt;
    }

private:
    float m_Mass;
    float m_Gravity;

    Vector2D m_Force;
    Vector2D m_Friction;

    Vector2D m_Position;
    Vector2D m_Velocity;
    Vector2D m_Accelaration;
};

#endif /* _RIGID_BODY_H_ */
