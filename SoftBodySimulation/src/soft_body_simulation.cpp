#include "soft_body_simulation.h"

#include <particle_system/particle_system.h>
#include <control_box.h>

SoftBodySimulation::SoftBodySimulation(
        std::shared_ptr<ParticleSystem> particle_system,
        std::shared_ptr<ControlBox> control_box)
        : particle_system_(particle_system),
          control_box_(control_box) {}
SoftBodySimulation::~SoftBodySimulation(){}

void SoftBodySimulation::Update(){
    if(!UpdateTime())
        return;
    particle_system_->StepSimulation(time_data_.time_delta);
    control_box_->Update();
}