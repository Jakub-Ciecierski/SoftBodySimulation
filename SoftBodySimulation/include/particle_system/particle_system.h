#ifndef PROJECT_PARTICLE_SYSTEM_H
#define PROJECT_PARTICLE_SYSTEM_H

#include <vector>
#include <memory>

namespace ifx{
class SceneContainer;
}

class Particle;
class Constraint;

class ParticleSystem {
public:

    ParticleSystem(std::shared_ptr<ifx::SceneContainer> scene);
    ~ParticleSystem();

    float* damping(){return &damping_;}

    std::vector<std::shared_ptr<Particle>>& particles(){return particles_;}
    std::vector<std::shared_ptr<Constraint>>& constraints(){
        return constraints_;}

    void AddParticle(std::shared_ptr<Particle> particle);
    void AddConstraint(std::shared_ptr<Constraint> constraint);

    void StepSimulation(float dt);

private:
    void UpdateParticle(std::shared_ptr<Particle> particle, float dt);

    std::vector<std::shared_ptr<Particle>> particles_;
    std::vector<std::shared_ptr<Constraint>> constraints_;

    float damping_;

    std::shared_ptr<ifx::SceneContainer> scene_;
};


#endif //PROJECT_PARTICLE_SYSTEM_H
