#ifndef PROJECT_BEZIER_CUBE_H
#define PROJECT_BEZIER_CUBE_H

#include <memory>
#include <math/math_ifx.h>

namespace ifx{
class GameObject;
class Mesh;
}

class Program;
class ParticleSystem;

struct BezierPoints{
    glm::mat4 X;
    glm::mat4 Y;
    glm::mat4 Z;
};

class BezierCube {
public:
    BezierCube(std::shared_ptr<ParticleSystem> particle_system);
    ~BezierCube();

    bool show(){return show_;}
    void show(bool v ){show_ = v;}

    void UpdateGameObject();
private:
    std::shared_ptr<Program> LoadProgram();

    BezierPoints CreateBackFace();
    BezierPoints CreateFrontFace();
    BezierPoints CreateTopFace();
    BezierPoints CreateDownFace();
    BezierPoints CreateLeftFace();
    BezierPoints CreateRightFace();

    std::unique_ptr<ifx::Mesh> CreateMesh(BezierPoints points);
    std::shared_ptr<ParticleSystem> particle_system_;

    std::shared_ptr<ifx::GameObject> game_object_;

    bool show_;
};

#endif //PROJECT_BEZIER_CUBE_H

