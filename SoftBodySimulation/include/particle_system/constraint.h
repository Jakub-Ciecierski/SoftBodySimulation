#ifndef PROJECT_CONSTRAINT_H
#define PROJECT_CONSTRAINT_H

#include <memory>

namespace ifx{
class GameObject;
}

class Particle;

class Constraint {
public:
    Constraint(std::shared_ptr<Particle> particle_a,
               std::shared_ptr<Particle> particle_b,
               bool generate_render_object = false);
    virtual ~Constraint();

    std::shared_ptr<Particle> particle_a(){return particle_a_;}
    std::shared_ptr<Particle> particle_b(){return particle_b_;}

    std::shared_ptr<ifx::GameObject> game_object(){return game_object_;}

    virtual void ComputeForce() = 0;

    void UpdateGameObject();
protected:
    std::shared_ptr<Particle> particle_a_;
    std::shared_ptr<Particle> particle_b_;

    std::shared_ptr<ifx::GameObject> game_object_;

    bool generate_render_object_;

};


#endif //PROJECT_CONSTRAINT_H
