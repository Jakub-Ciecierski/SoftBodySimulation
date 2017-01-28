#include "collision/collision_handler.h"

#include <particle_system/particle.h>
#include <collision/collision_state.h>
#include <room.h>
#include <math/print_math.h>
#include <iostream>

CollisionHandler::CollisionHandler(std::shared_ptr<Room> room) :
    restitution_(1.0f),
    room_(room){}

CollisionHandler::~CollisionHandler(){}

void CollisionHandler::HandleCollision(std::shared_ptr<Particle> particle,
                                       const CollisionState& collision_state){
    if(collision_state.floor)
        HandleFloorCeilingCollision(particle);
    if(collision_state.ceiling)
        HandleFloorCeilingCollision(particle);

    if(collision_state.left_wall)
        HandleLeftRightWallCollision(particle);
    if(collision_state.right_wall)
        HandleLeftRightWallCollision(particle);

    if(collision_state.front_wall)
        HandleFrontBackWallCollision(particle);
    if(collision_state.back_wall)
        HandleFrontBackWallCollision(particle);

}

void CollisionHandler::HandleFloorCeilingCollision(
        std::shared_ptr<Particle> particle){
    auto& velocity = particle->velocity();
    auto new_velocity = glm::vec3(velocity.x,
                                  -velocity.y,
                                  velocity.z);
    new_velocity = restitution_ * new_velocity;
/*
    ifx::PrintVec3(velocity);
    ifx::PrintVec3(new_velocity);
    ifx::PrintVec3(particle->last_position());
    ifx::PrintVec3(particle->position());
    std::cout << std::endl;
*/
    particle->velocity(new_velocity);


/*
    auto& floor_position = room_->floor->getPosition();
    auto& position = particle->position();
    if(particle->position().y < floor_position.y){
        particle->position(glm::vec3(
                position.x, floor_position.y, position.z
        ));
    }*/
}

void CollisionHandler::HandleLeftRightWallCollision(
        std::shared_ptr<Particle> particle){
    auto& velocity = particle->velocity();
    auto new_velocity = glm::vec3(velocity.x,
                                  velocity.y,
                                  -velocity.z);
    new_velocity = restitution_ * new_velocity;
    particle->velocity(new_velocity);
}

void CollisionHandler::HandleFrontBackWallCollision(
        std::shared_ptr<Particle> particle){
    auto& velocity = particle->velocity();
    auto new_velocity = glm::vec3(-velocity.x,
                                  velocity.y,
                                  velocity.z);
    new_velocity = restitution_ * new_velocity;
    particle->velocity(new_velocity);
}