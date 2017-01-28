#include "particle_system/particle_system.h"

#include <particle_system/constraint.h>
#include <particle_system/particle.h>

#include <game/scene_container.h>
#include <math/print_math.h>
#include <iostream>
#include <collision/collision_detector.h>
#include <collision/collision_handler.h>
#include <collision/collision_state.h>
#include <factory/collision_room_factory.h>
#include <room.h>
#include <object/render_object.h>

ParticleSystem::ParticleSystem(std::shared_ptr<ifx::SceneContainer> scene) :
    scene_(scene),
    damping_(10.0f),
    gravity_force_(glm::vec3(0,0,0)),
    draw_constraints_(false),
    draw_particles_(true){
    auto room = CollisionRoomFactory().Create();
    collision_detector_ = std::shared_ptr<CollisionDetector>(
            new CollisionDetector(room));
    collision_handler_ = std::shared_ptr<CollisionHandler>(
            new CollisionHandler(room));

    AddRoomToScene();
}

ParticleSystem::~ParticleSystem(){
    for(auto& particle : particles_){
        if(particle->game_object())
            scene_->Remove(particle->game_object());
    }
    for(auto& constraint : constraints_){
        if(constraint->game_object())
            scene_->Remove(constraint->game_object());
    }
    RemoveRoomToScene();
}

void ParticleSystem::AddParticle(std::shared_ptr<Particle> particle){
    particles_.push_back(particle);
    if(particle->game_object())
        scene_->Add(particle->game_object());
}

void ParticleSystem::AddConstraint(std::shared_ptr<Constraint> constraint){
    constraints_.push_back(constraint);
}

void ParticleSystem::StepSimulation(float dt){
    for(auto& constraint : constraints_)
        constraint->ComputeForce();
    for(auto& particle : particles_)
        UpdateParticle(particle, dt);

    if(draw_constraints_)
        UpdateConstraintGameObjects();
}

void ParticleSystem::UpdateParticle(std::shared_ptr<Particle> particle,
                                    float dt){
    UpdateParticleAcceleration(particle);
    UpdateParticleVelocity(particle, dt);
    UpdateParticlePosition(particle, dt);

    HandleCollisions(particle, dt);

    particle->ResetForce();
}

void ParticleSystem::UpdateParticleAcceleration(
        std::shared_ptr<Particle> particle){
    auto force = particle->force();

    auto damping_force = -(damping_ * particle->velocity());
    force += damping_force;
    force += gravity_force_;

    particle->acceleration(force / (*particle->mass()));
}

void ParticleSystem::UpdateParticleVelocity(
        std::shared_ptr<Particle> particle, float dt){
    glm::vec3 new_velocity
            = particle->velocity() + dt * particle->acceleration();
    particle->velocity(new_velocity);
}
void ParticleSystem::UpdateParticlePosition(
        std::shared_ptr<Particle> particle, float dt){
    glm::vec3 new_position = particle->position() + dt * particle->velocity();
/*s
    ifx::PrintVec3(particle->position());
    ifx::PrintVec3(new_position);
*/
    particle->position(new_position);
}

void ParticleSystem::HandleCollisions(std::shared_ptr<Particle> particle,
                                      float dt){
    auto collision_state = collision_detector_->ComputeCollisionState(particle);

    while(collision_state.FoundCollision()){
        collision_handler_->HandleCollision(particle, collision_state);

        particle->position(particle->last_position());

        UpdateParticlePosition(particle, dt);
        collision_state = collision_detector_->ComputeCollisionState(particle);
    }
}

void ParticleSystem::UpdateConstraintGameObjects(){
    for(auto& constraint : constraints_){
        if(constraint->game_object()){
            scene_->Remove(constraint->game_object());
            if(draw_constraints_){
                constraint->UpdateGameObject();
                scene_->Add(constraint->game_object());
            }
        }
    }
}

void ParticleSystem::AddRoomToScene(){
    if(collision_detector_->room()->floor)
        scene_->Add(collision_detector_->room()->floor);
    if(collision_detector_->room()->ceiling)
        scene_->Add(collision_detector_->room()->ceiling);

    if(collision_detector_->room()->left_wall)
        scene_->Add(collision_detector_->room()->left_wall);
    if(collision_detector_->room()->right_wall)
        scene_->Add(collision_detector_->room()->right_wall);

    if(collision_detector_->room()->front_wall)
        scene_->Add(collision_detector_->room()->front_wall);
    if(collision_detector_->room()->back_wall)
        scene_->Add(collision_detector_->room()->back_wall);
}
void ParticleSystem::RemoveRoomToScene(){
    if(collision_detector_->room()->floor)
        scene_->Remove(collision_detector_->room()->floor);
    if(collision_detector_->room()->ceiling)
        scene_->Remove(collision_detector_->room()->ceiling);

    if(collision_detector_->room()->left_wall)
        scene_->Remove(collision_detector_->room()->left_wall);
    if(collision_detector_->room()->right_wall)
        scene_->Remove(collision_detector_->room()->right_wall);

    if(collision_detector_->room()->front_wall)
        scene_->Remove(collision_detector_->room()->front_wall);
    if(collision_detector_->room()->back_wall)
        scene_->Remove(collision_detector_->room()->back_wall);
}

void ParticleSystem::draw_particles(bool v){
    draw_particles_ = v;

    for(auto& particle : particles_){
        auto render_objects = particle->game_object()->GetComponents();
        auto render_obect = std::static_pointer_cast<ifx::RenderObject>(
                render_objects[0]);
        render_obect->do_render(draw_particles_);
    }
}