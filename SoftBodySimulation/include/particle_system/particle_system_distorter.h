#ifndef PROJECT_PARTICLE_SYSTEM_DISTORTER_H
#define PROJECT_PARTICLE_SYSTEM_DISTORTER_H

#include <memory>

class ParticleSystem;

class ParticleSystemDistorter {
public:
    ParticleSystemDistorter();
    ~ParticleSystemDistorter();

    void DistortParticlesVelocity(
            std::shared_ptr<ParticleSystem> particle_system);
private:
};


#endif //PROJECT_PARTICLE_SYSTEM_DISTORTER_H
