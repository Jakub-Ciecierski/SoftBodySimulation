#ifndef PROJECT_CONTROL_BOX_H
#define PROJECT_CONTROL_BOX_H

#include <vector>
#include <memory>

namespace ifx{
class GameObject;
}

class Particle;

class ControlBox {
public:

    ControlBox(std::shared_ptr<ifx::GameObject> game_object, float a);
    ~ControlBox();

    std::vector<std::shared_ptr<Particle>>& particles(){return particles_;}
    std::shared_ptr<ifx::GameObject> game_object(){return game_object_;}
    float a(){return a_;};

    void Update();
private:
    void InitParticles();

    std::vector<std::shared_ptr<Particle>> particles_;

    std::shared_ptr<ifx::GameObject> game_object_;
    float a_;
};


#endif //PROJECT_CONTROL_BOX_H
