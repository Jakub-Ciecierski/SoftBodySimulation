#include "particle_system/particle_system_distorter.h"

#include <math/math_ifx.h>
#include <particle_system/particle_system.h>
#include <particle_system/particle.h>

#include <random>

ParticleSystemDistorter::ParticleSystemDistorter(){}
ParticleSystemDistorter::~ParticleSystemDistorter(){}

void ParticleSystemDistorter::DistortParticlesVelocity(
        std::shared_ptr<ParticleSystem> particle_system){
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    auto& particles = particle_system->particles();
    for(auto& particle : particles){
        glm::vec3 random_velocity(
                distribution(generator),
                distribution(generator),
                distribution(generator));
        //random_velocity = glm::vec3(0, 0.1, 0);
        particle->velocity(random_velocity);
    }
}