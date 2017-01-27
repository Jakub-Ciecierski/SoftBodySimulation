#ifndef PROJECT_CONTROL_BOX_H
#define PROJECT_CONTROL_BOX_H

#include <vector>
#include <memory>

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

    std::vector<std::shared_ptr<Particle>> particles_;
    std::vector<std::shared_ptr<Constraint>> constraints_;

    std::shared_ptr<ifx::GameObject> game_object_;
    float a_;
};


#endif //PROJECT_CONTROL_BOX_H
