#include "particle_system/constraint.h"

#include <particle_system/particle.h>
#include <graphics/factory/render_object_factory.h>
#include <object/game_object.h>

Constraint::Constraint(std::shared_ptr<Particle> particle_a,
                       std::shared_ptr<Particle> particle_b,
                       bool generate_render_object) :
        particle_a_(particle_a),
        particle_b_(particle_b),
        game_object_(nullptr),
        generate_render_object_(generate_render_object){
    UpdateGameObject();
}

Constraint::~Constraint(){}

void Constraint::UpdateGameObject(){
    if(!generate_render_object_)
        return;
    game_object_ = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    auto render_object = ifx::RenderObjectFactory().CreateLine(
            particle_a_->game_object()->getPosition(),
            particle_b_->game_object()->getPosition(),
            glm::vec3(0,255,0));

    game_object_->Add(render_object);
}