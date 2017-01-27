#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx{
class GameObject;
}

class Particle {
public:

    Particle();
    ~Particle();

    const glm::vec3& force(){return force_;}
    float* mass(){return &mass_;}
    void mass(float v){mass_ = v;}

    const glm::vec3& position();
    void position(const glm::vec3& pos);

    const glm::vec3& velocity(){return velocity_;}
    void velocity(const glm::vec3& vel){velocity_ = vel;}

    std::shared_ptr<ifx::GameObject> game_object(){return game_object_;}

    void ApplyForce(const glm::vec3& force){
        force_ += force;
    }
    void ResetForce(){
        force_ = glm::vec3(0.0f, 0.0f, 0.0f);
    }

private:
    void InitGameObject();

    glm::vec3 force_;
    float mass_;
    glm::vec3 velocity_;

    std::shared_ptr<ifx::GameObject> game_object_;
};


#endif //PROJECT_PARTICLE_H
