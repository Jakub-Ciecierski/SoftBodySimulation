#include "control_box.h"

#include <particle_system/particle.h>
#include <object/game_object.h>

ControlBox::ControlBox(std::shared_ptr<ifx::GameObject> game_object, float a)
        : game_object_(game_object), a_(a){
    InitParticles();
}

ControlBox::~ControlBox(){}

void ControlBox::Update(){
    auto& box_position = game_object_->getPosition();
    auto a_half = a_ / 2.0f;
    float x = box_position.x;
    float y = box_position.y;
    float z = box_position.z;

    particles_[0]->position(glm::vec3(x - a_half,y- a_half,z- a_half));
    particles_[0]->velocity(glm::vec3(0,0,0));

    particles_[1]->position(glm::vec3(x + a_half,y - a_half,z- a_half));
    particles_[1]->velocity(glm::vec3(0,0,0));

    particles_[2]->position(glm::vec3(x - a_half, y- a_half, z + a_half));
    particles_[2]->velocity(glm::vec3(0,0,0));

    particles_[3]->position(glm::vec3(x + a_half, y - a_half, z+ a_half));
    particles_[3]->velocity(glm::vec3(0,0,0));

    particles_[4]->position(glm::vec3(x - a_half, y + a_half, z - a_half));
    particles_[4]->velocity(glm::vec3(0,0,0));

    particles_[5]->position(glm::vec3(x + a_half, y + a_half, z - a_half));
    particles_[5]->velocity(glm::vec3(0,0,0));

    particles_[6]->position(glm::vec3(x - a_half, y+ a_half, z + a_half));
    particles_[6]->velocity(glm::vec3(0,0,0));

    particles_[7]->position(glm::vec3(x + a_half, y+ a_half, z+ a_half));
    particles_[7]->velocity(glm::vec3(0,0,0));
}

void ControlBox::InitParticles(){
    auto& box_position = game_object_->getPosition();
    auto a_half = a_ / 2.0f;
    float x = box_position.x;
    float y = box_position.y;
    float z = box_position.z;

    auto particle1 = std::shared_ptr<Particle>(new Particle());
    particle1->position(glm::vec3(x - a_half,y- a_half,z- a_half));
    particles_.push_back(particle1);

    auto particle2 = std::shared_ptr<Particle>(new Particle());
    particle2->position(glm::vec3(x + a_half,y - a_half,z- a_half));
    particles_.push_back(particle2);

    auto particle3 = std::shared_ptr<Particle>(new Particle());
    particle3->position(glm::vec3(x - a_half, y- a_half, z + a_half));
    particles_.push_back(particle3);

    auto particle4 = std::shared_ptr<Particle>(new Particle());
    particle4->position(glm::vec3(x + a_half, y - a_half, z+ a_half));
    particles_.push_back(particle4);

    auto particle5 = std::shared_ptr<Particle>(new Particle());
    particle5->position(glm::vec3(x - a_half, y + a_half, z - a_half));
    particles_.push_back(particle5);

    auto particle6 = std::shared_ptr<Particle>(new Particle());
    particle6->position(glm::vec3(x + a_half, y + a_half, z - a_half));
    particles_.push_back(particle6);

    auto particle7 = std::shared_ptr<Particle>(new Particle());
    particle7->position(glm::vec3(x - a_half, y+ a_half, z + a_half));
    particles_.push_back(particle7);

    auto particle8 = std::shared_ptr<Particle>(new Particle());
    particle8->position(glm::vec3(x + a_half, y+ a_half, z+ a_half));
    particles_.push_back(particle8);
}