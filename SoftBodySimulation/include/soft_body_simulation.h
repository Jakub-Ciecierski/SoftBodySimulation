#ifndef PROJECT_SOFT_BODY_SIMULATION_H
#define PROJECT_SOFT_BODY_SIMULATION_H

#include <vr/simulation.h>

#include <memory>

class ParticleSystem;
class ControlBox;
class BezierCube;

class SoftBodySimulation : public ifx::Simulation {
public:

    SoftBodySimulation(std::shared_ptr<ParticleSystem> particle_system,
                       std::shared_ptr<ControlBox> control_box);
    ~SoftBodySimulation();

    std::shared_ptr<ParticleSystem> particle_system(){return particle_system_;}
    std::shared_ptr<ControlBox> control_box(){return control_box_;}
    std::shared_ptr<BezierCube> bezier_cube(){return bezier_cube_;}
    virtual void Update() override;
private:
    std::shared_ptr<ParticleSystem> particle_system_;
    std::shared_ptr<ControlBox> control_box_;
    std::shared_ptr<BezierCube> bezier_cube_;

};


#endif //PROJECT_SOFT_BODY_SIMULATION_H
