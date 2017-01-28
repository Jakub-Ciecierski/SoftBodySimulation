#include "collision/collision_detector.h"

#include <particle_system/particle.h>
#include <collision/collision_state.h>
#include <room.h>

CollisionDetector::CollisionDetector(std::shared_ptr<Room> room)
        : room_(room){}
CollisionDetector::~CollisionDetector(){}

CollisionState CollisionDetector::ComputeCollisionState(
        std::shared_ptr<Particle> particle){
    CollisionState collision_state;
    if(!particle->detect_collision())
        return collision_state;

    collision_state.floor = CheckFloorCollision(particle);
    collision_state.ceiling = CheckCeilingCollision(particle);

    collision_state.left_wall = CheckLeftWallCollision(particle);
    collision_state.right_wall = CheckRightWallCollision(particle);

    collision_state.front_wall = CheckFrontWallCollision(particle);
    collision_state.back_wall = CheckBackWallCollision(particle);

    return collision_state;
}

bool CollisionDetector::CheckFloorCollision(std::shared_ptr<Particle> particle){
    auto& floor_position = room_->floor->getPosition();
    const auto epsilon = 0.01f;
    return ((particle->position().y + epsilon) < floor_position.y);
}

bool CollisionDetector::CheckCeilingCollision(std::shared_ptr<Particle> particle){
    auto& floor_position = room_->ceiling->getPosition();
    return ((particle->position().y) > floor_position.y);
}

bool CollisionDetector::CheckLeftWallCollision(
        std::shared_ptr<Particle> particle){
    auto& floor_position = room_->left_wall->getPosition();
    return (particle->position().z < floor_position.z);
}

bool CollisionDetector::CheckRightWallCollision(
        std::shared_ptr<Particle> particle){
    auto& floor_position = room_->right_wall->getPosition();
    return (particle->position().z > floor_position.z);
}

bool CollisionDetector::CheckFrontWallCollision(
        std::shared_ptr<Particle> particle){
    auto& floor_position = room_->front_wall->getPosition();
    return (particle->position().x > floor_position.x);
}

bool CollisionDetector::CheckBackWallCollision(
        std::shared_ptr<Particle> particle){
    auto& floor_position = room_->back_wall->getPosition();
    return (particle->position().x < floor_position.x);
}