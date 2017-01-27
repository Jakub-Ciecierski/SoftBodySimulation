#ifndef PROJECT_CONTROL_BOX_H
#define PROJECT_CONTROL_BOX_H

#include <vector>
#include <memory>
#include <math/math_ifx.h>

namespace ifx{
class GameObject;
}

class Constraint;
class Particle;

class ControlBox {
public:

    ControlBox(std::shared_ptr<ifx::GameObject> game_object, float a);
    ~ControlBox();

    std::vector<std::shared_ptr<Constraint>>& constraints(){return constraints_;}
    std::vector<std::shared_ptr<Particle>>& particles(){return particles_;}
    std::shared_ptr<ifx::GameObject> game_object(){return game_object_;}
    float a(){return a_;};

    void Update();

    void AddConstraint(std::shared_ptr<Constraint> constraint);
private:
    void InitParticles();

    void UpdateParticlePosition();
    void TransformParticle(std::shared_ptr<Particle> particle,
                           glm::vec3 init_postion);
    void UpdateParticleVelocity();

    std::vector<std::shared_ptr<Particle>> particles_;
    std::vector<std::shared_ptr<Constraint>> constraints_;

    std::shared_ptr<ifx::GameObject> game_object_;
    float a_;
};


#endif //PROJECT_CONTROL_BOX_H
