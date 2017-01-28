#include "factory/soft_body_simulation_factory.h"

#include "factory/control_box_factory.h"
#include <soft_body_simulation.h>
#include <particle_system/particle_system.h>

SoftBodySimulationFactory::SoftBodySimulationFactory(){}
SoftBodySimulationFactory::~SoftBodySimulationFactory(){}

std::shared_ptr<SoftBodySimulation> SoftBodySimulationFactory::Create(
        std::shared_ptr<ifx::SceneContainer> scene){
    auto control_box = ControlBoxFactory().CreateControlBox();
    auto particle_system
            = std::shared_ptr<ParticleSystem>(new ParticleSystem(scene));
    auto simulation = std::shared_ptr<SoftBodySimulation>(
            new SoftBodySimulation(particle_system, control_box));

    return simulation;
}