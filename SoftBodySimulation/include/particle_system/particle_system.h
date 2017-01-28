#ifndef PROJECT_PARTICLE_SYSTEM_H
#define PROJECT_PARTICLE_SYSTEM_H

#include <vector>
#include <memory>

#include <math/math_ifx.h>

namespace ifx{
class SceneContainer;
}

class Particle;
class Constraint;
class CollisionDetector;
class CollisionHandler;

class ParticleSystem {
public:

    ParticleSystem(std::shared_ptr<ifx::SceneContainer> scene);
    ~ParticleSystem();

    float* damping(){return &damping_;}
    void damping(float v){damping_ = v;}

    const glm::vec3& gravity_force(){return gravity_force_;}
    void gravity_force(const glm::vec3& force){gravity_force_ = force;}

    std::vector<std::shared_ptr<Particle>>& particles(){return particles_;}
    std::vector<std::shared_ptr<Constraint>>& constraints(){
        return constraints_;}

    std::shared_ptr<CollisionHandler> collision_handler(){
        return collision_handler_;
    };

    bool draw_constraints(){return draw_constraints_;}
    void draw_constraints(bool v){
            draw_constraints_ = v;
            UpdateConstraintGameObjects();
    }

    void AddParticle(std::shared_ptr<Particle> particle);
    void AddConstraint(std::shared_ptr<Constraint> constraint);

    void StepSimulation(float dt);

private:
    void UpdateParticle(std::shared_ptr<Particle> particle, float dt);
    void UpdateParticleAcceleration(std::shared_ptr<Particle> particle);
    void UpdateParticleVelocity(std::shared_ptr<Particle> particle, float dt);
    void UpdateParticlePosition(std::shared_ptr<Particle> particle, float dt);
    void HandleCollisions(std::shared_ptr<Particle> particle, float dt);

    void UpdateConstraintGameObjects();

    void AddRoomToScene();
    void RemoveRoomToScene();

    std::shared_ptr<CollisionDetector> collision_detector_;
    std::shared_ptr<CollisionHandler> collision_handler_;

    std::vector<std::shared_ptr<Particle>> particles_;
    std::vector<std::shared_ptr<Constraint>> constraints_;

    float damping_;
    std::shared_ptr<ifx::SceneContainer> scene_;

    glm::vec3 gravity_force_;

    bool draw_constraints_;
};


#endif //PROJECT_PARTICLE_SYSTEM_H

