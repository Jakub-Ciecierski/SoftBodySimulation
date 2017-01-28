#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx{
class GameObject;
}

class Particle {
public:

    Particle(bool detect_collision = true);
    ~Particle();

    const glm::vec3& force(){return force_;}
    float* mass(){return &mass_;}
    void mass(float v){mass_ = v;}

    const glm::vec3& position();
    void position(const glm::vec3& pos);
    glm::vec3 last_position(){return last_position_;}

    const glm::vec3& velocity(){return velocity_;}
    void velocity(const glm::vec3& vel){velocity_ = vel;}

    const glm::vec3& acceleration(){return acceleration_;}
    void acceleration(const glm::vec3& vel){acceleration_ = vel;}

    bool detect_collision(){return detect_collision_;}

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
    glm::vec3 acceleration_;
    glm::vec3 last_position_;

    bool detect_collision_;

    std::shared_ptr<ifx::GameObject> game_object_;
};


#endif //PROJECT_PARTICLE_H
