#include "particle_system/particle.h"

#include <graphics/factory/render_object_factory.h>
#include <graphics/model/material.h>
#include <graphics/factory/texture_factory.h>
#include <graphics/model/mesh.h>
#include <graphics/model/model.h>

#include <object/game_object.h>

Particle::Particle() :
        mass_(1.0f),
        velocity_(glm::vec3(0,0,0)){
    InitGameObject();
    ResetForce();
}
Particle::~Particle(){}

const glm::vec3& Particle::position(){
    return game_object_->getPosition();
}
void Particle::position(const glm::vec3& pos){
    game_object_->moveTo(pos);
}

void Particle::InitGameObject(){
    game_object_ = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto render_object = ifx::RenderObjectFactory().CreateCube();
    auto material = std::shared_ptr<ifx::Material>(new ifx::Material());
    material->diffuse = ifx::TextureFactory().CreateSolidColorTexture(
            glm::vec3(0,255,0), ifx::TextureTypes::DIFFUSE);
    material->specular = ifx::TextureFactory().CreateSolidColorTexture(
            glm::vec3(0,255,0), ifx::TextureTypes::SPECULAR);

    render_object->models()[0]->getMesh(0)->material(material);

    game_object_->Add(render_object);
    game_object_->scale(0.05);
}