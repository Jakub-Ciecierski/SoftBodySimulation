#include <math/math_ifx.h>
#include <math/print_math.h>
#include <iostream>

#include "particle_system/spring/spring_constraint.h"
#include "particle_system/particle.h"
#include "object/game_object.h"

SpringConstraint::SpringConstraint(std::shared_ptr<Particle> particle_a,
                                   std::shared_ptr<Particle> particle_b,
                                   bool generate_render_object) :
        Constraint(particle_a, particle_b,
                   generate_render_object),
        spring_coefficient_(1.2f),
        is_control_box_(false){
    rest_length_
            = ifx::EuclideanDistance(particle_a_->game_object()->getPosition(),
                                     particle_b_->game_object()->getPosition());
}

SpringConstraint::SpringConstraint(std::shared_ptr<Particle> particle_a,
                                   std::shared_ptr<Particle> particle_b,
                                   float rest_length,
                                   bool generate_render_object) :
        Constraint(particle_a, particle_b,
                   generate_render_object),
        spring_coefficient_(0.2f),
        rest_length_(rest_length),
        is_control_box_(false){}

SpringConstraint::~SpringConstraint(){}

void SpringConstraint::ComputeForce(){
    const float epsilon = 0.0001f;
    auto& position_a = particle_a_->position();
    auto& position_b = particle_b_->position();
    auto difference_ab = position_b - position_a;

    auto current_length = ifx::Magnitude(difference_ab);
    auto direction = glm::normalize(difference_ab);

    if(current_length < epsilon)
        direction = glm::vec3(0, 0, 0);

    auto spring_length = current_length - rest_length_;
    auto force_magnitude = -spring_coefficient_ * spring_length;
    auto force = direction * force_magnitude;

    particle_a_->ApplyForce(-force);
    particle_b_->ApplyForce(force);
}