#ifndef _CLIMAT_EMITTER_H_
#define _CLIMAT_EMITTER_H_

#include <vector>
#include "particle.h"
#include "physics/transform.h"

#define RAIN_PARTICLE_COUNT 800
#define SNOW_PARTICLE_COUNT 400
#define THUNDER_PARTICLE_COUNT 1
#define DUST_PARTICLE_COUNT 50

enum Climat {
    DUST = 0,
    RAIN,
    SNOW,
    LIGHTNING
};

class ClimatEmitter {
public:
    ClimatEmitter(Climat clmt = DUST) {
        InitParticles(clmt);
    }

    ~ClimatEmitter() {
        for (auto particle : m_Particles)
            delete particle;
        m_Particles.clear();
    }

    void InitParticles(Climat clmt = DUST) {
        m_CurrentClimat = clmt;
        m_Particles.clear();
        m_ParticleTextureID.clear();

        switch (m_CurrentClimat) {
        case RAIN:
            m_ParticleTextureID = {"rain1", "rain2", "rain3"};
            m_ParticleCount = RAIN_PARTICLE_COUNT;
            break;
        case SNOW:
            m_ParticleTextureID = {"snow1", "snow2", "snow3"};
            m_ParticleCount = SNOW_PARTICLE_COUNT;
            break;
        case LIGHTNING:
            m_ParticleTextureID = {"light1", "light2", "light3"};
            m_ParticleCount = THUNDER_PARTICLE_COUNT;
            break;
        default:
            m_ParticleTextureID = {"dust1", "dust2", "dust3"};
            m_ParticleCount = DUST_PARTICLE_COUNT;
            break;
        }

        for (int i = 0; i < m_ParticleCount; i++) {
            m_Particles.push_back(NewParticle());
        }
    }

    void UpdateParticles(float dt) {
        for (int i = 0; i < m_Partiles.size(); i++) {
            if (m_Partiles[i]->IsDead()) {
                delete m_Partiles[i];
                m_Partiles[i] = NewParticle();
            } else {
                m_Partiles[i]->Move(dt);
            }
        }
    }

    void RenderParticles() {
        for (auto particle : m_Particles)
            particle->Show();
    }

private:
    Particle *NewParticle() {
        int index = Helpers::RandI(0, m_ParticleTextureID.size());
        switch (m_CurrentClimat) {
        case RAIN:
            return RainParticle(m_ParticleTextureID[index]);
        case SNOW:
            return SnowParticle(m_ParticleTextureID[index]);
        case LIGHTNING:
            return ThunderParticle(m_ParticleTextureID[index]);
        default:
            return DustParticle(m_ParticleTextureID[index]);
        }
    }

    Particle *RainParticle(std::string textureID) {
        SDL_Rect vp = Engine::GetInstance()->GetViewPort();
        float x = Helpers::RandI(0, vp.w);
        float vx = Helpers::RandI(-1, 1);
        float vy = Helpers::RandI(10, 15);
        Uint32 lifetime = Helpers::RandI(800, 2000);
        return (new Particle(Transform(x, 0, 0, 0, textureID), vx, vy, lifetime));
    }

    Particle *SnowParticle(std::string textureID) {
        SDL_Rect vp = Engine::GetInstance()->GetViewPort();
        float x = Helpers::RandI(0, vp.w);
        float vx = Helpers::RandI(-2, 2);
        float vy = Helpers::RandI(1, 4);
        Uint32 lifetime = Helpers::RandI(5000, 8000);
        return (new Particle(Transform(x, 0, 0, 0, textureID), vx, vy, lifetime));
    }

    Particle *ThunderParticle(std::string textureID) {
        SDL_Rect vp = Engine::GetInstance()->GetViewPort();
        float x = Helpers::RandI(0, vp.w);
        float y = Helpers::RandI(0, 100);
        Uint32 lifetime = Helpers::RandI(600, 1200);
        return (new Particle(Transform(x, y, 0, 0, textureID), 0, 0, lifetime));
    }

    Particle *DustParticle(std::string textureID) {
        SDL_Rect vp = Engine::GetInstance()->GetViewPort();
        float y = Helpers::RandI(0, vp.h);
        float vx = Helpers::RandI(-10, -1);
        float vy = Helpers::RandI(-1, 1);
        Uint32 lifetime = Helpers::RandI(4000, 9000);
        return (new Particle(Transform(vp.w, y, 0, 0, textureID), vx, vy, lifetime));
    }

private:
    std::vector<Particle *> m_Particles;
    Climat m_CurrentClimat;
    Uint32 m_ParticleCount;
    std::vector<std::string> m_ParticleTextureID;
};

#endif /* _CLIMAT_EMITTER_H_ */
