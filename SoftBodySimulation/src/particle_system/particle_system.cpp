#include "particle_system/particle_system.h"

#include <particle_system/constraint.h>
#include <particle_system/particle.h>

#include <game/scene_container.h>
#include <math/print_math.h>
#include <iostream>

ParticleSystem::ParticleSystem(std::shared_ptr<ifx::SceneContainer> scene) :
    scene_(scene),
    damping_(10.0f){}
ParticleSystem::~ParticleSystem(){
    for(auto& particle : particles_)
        scene_->Remove(particle->game_object());
    for(auto& constraint : constraints_)
        scene_->Remove(constraint->game_object());
}

void ParticleSystem::AddParticle(std::shared_ptr<Particle> particle){
    particles_.push_back(particle);
    scene_->Add(particle->game_object());
}

void ParticleSystem::AddConstraint(std::shared_ptr<Constraint> constraint){
    constraints_.push_back(constraint);
    scene_->Add(constraint->game_object());
}

void ParticleSystem::StepSimulation(float dt){
    for(auto& constraint : constraints_)
        constraint->ComputeForce();
    for(auto& particle : particles_)
        UpdateParticle(particle, dt);
}

void ParticleSystem::UpdateParticle(std::shared_ptr<Particle> particle,
                                    float dt){
    auto force = particle->force();

    force += -(damping_ * particle->velocity());
/*
    ifx::PrintVec3(force);
    ifx::PrintVec3(particle->velocity());
    ifx::PrintVec3(particle->position());
    std::cout << std::endl;
*/

    glm::vec3 acceleration = force / (*particle->mass());
    glm::vec3 velocity = particle->velocity() + dt * acceleration;
    glm::vec3 position = particle->position() + dt * velocity;

    particle->velocity(velocity);
    particle->position(position);

    particle->ResetForce();
}