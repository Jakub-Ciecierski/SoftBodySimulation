#ifndef PROJECT_SPRING_CONSTRAINT_H
#define PROJECT_SPRING_CONSTRAINT_H

#include <particle_system/constraint.h>

class SpringConstraint : public Constraint{
public:
    SpringConstraint(std::shared_ptr<Particle> particle_a,
                     std::shared_ptr<Particle> particle_b);
    SpringConstraint(std::shared_ptr<Particle> particle_a,
                     std::shared_ptr<Particle> particle_b,
                     float rest_length);
    ~SpringConstraint();

    float* spring_coefficient(){return &spring_coefficient_;}

    virtual void ComputeForce() override;
private:
    float rest_length_;
    float spring_coefficient_;

};


#endif //PROJECT_SPRING_CONSTRAINT_H
