#include <math/math_ifx.h>
#include <math/print_math.h>
#include <iostream>

#include "particle_system/spring/spring_constraint.h"
#include "particle_system/particle.h"
#include "object/game_object.h"

SpringConstraint::SpringConstraint(std::shared_ptr<Particle> particle_a,
                                   std::shared_ptr<Particle> particle_b) :
        Constraint(particle_a, particle_b),
        spring_coefficient_(0.2f){
    rest_length_
            = ifx::EuclideanDistance(particle_a_->game_object()->getPosition(),
                                     particle_b_->game_object()->getPosition());
}

SpringConstraint::SpringConstraint(std::shared_ptr<Particle> particle_a,
                                   std::shared_ptr<Particle> particle_b,
                                   float rest_length) :
        Constraint(particle_a, particle_b),
        spring_coefficient_(0.2f),
        rest_length_(rest_length){}

SpringConstraint::~SpringConstraint(){}

void SpringConstraint::ComputeForce(){
    const float e = 0.0001f;
    auto& position_a = particle_a_->position();
    auto& position_b = particle_b_->position();
    auto difference_ab = position_b - position_a;

    auto current_length = ifx::Magnitude(difference_ab);
    auto direction = glm::normalize(difference_ab);
    if(current_length < e){
        direction = glm::vec3(0, 1, 0);
    }
    auto I = current_length - rest_length_;
    float force_magnitude = -spring_coefficient_ * I;

    auto force = direction * force_magnitude;

    ifx::PrintVec3(position_a);
    ifx::PrintVec3(position_b);
    ifx::PrintVec3(difference_ab);
    std::cout << "I: " << I << std::endl;
    std::cout << "f: " << force_magnitude << std::endl;
    std::cout << std::endl;

    if(std::isnan(force.x))
        std::cout << "why" << std::endl;

    particle_a_->ApplyForce(-force);
    particle_b_->ApplyForce(force);
}