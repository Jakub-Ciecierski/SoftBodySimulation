#include "control_box.h"

#include <particle_system/particle.h>
#include <object/game_object.h>

ControlBox::ControlBox(std::shared_ptr<ifx::GameObject> game_object, float a)
        : game_object_(game_object), a_(a){
    InitParticles();
}

ControlBox::~ControlBox(){}

void ControlBox::Update(){
    UpdateParticlePosition();
    UpdateParticleVelocity();
}

void ControlBox::InitParticles(){
    /*
    const int count = 8;
    for(int i = 0; i < count; i++)
        particles_.push_back(std::shared_ptr<Particle>(new Particle()));
    Update();*/

    auto& position = game_object_->getPosition();
    float x = position.x;
    float y = position.y;
    float z = position.z;
    auto a_half = a_ / 2.0f;

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

void ControlBox::AddConstraint(std::shared_ptr<Constraint> constraint){
    constraints_.push_back(constraint);
}

void ControlBox::UpdateParticlePosition(){
    auto a_half = a_ / 2.0f;

    TransformParticle(particles_[0], glm::vec3(-a_half,-a_half,-a_half));
    TransformParticle(particles_[1], glm::vec3(a_half,-a_half,-a_half));
    TransformParticle(particles_[2], glm::vec3(-a_half,-a_half,+a_half));
    TransformParticle(particles_[3], glm::vec3(a_half,-a_half,a_half));
    TransformParticle(particles_[4], glm::vec3(-a_half,a_half,-a_half));
    TransformParticle(particles_[5], glm::vec3(a_half,a_half,-a_half));
    TransformParticle(particles_[6], glm::vec3(-a_half,a_half,a_half));
    TransformParticle(particles_[7], glm::vec3(a_half,a_half,a_half));
}

void ControlBox::TransformParticle(std::shared_ptr<Particle> particle,
                                   glm::vec3 init_postion){
    auto& model_matrix = game_object_->GetModelMatrix();
    auto position_4 = glm::vec4(init_postion, 1);

    position_4 = model_matrix * position_4;
    position_4.x /= position_4.w;
    position_4.y /= position_4.w;
    position_4.z /= position_4.w;

    particle->position(glm::vec3(position_4));
}

void ControlBox::UpdateParticleVelocity(){
    for(auto& particle : particles_)
        particle->velocity(glm::vec3(0,0,0));
}

