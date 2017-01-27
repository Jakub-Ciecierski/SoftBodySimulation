#ifndef PROJECT_SOFT_BODY_SIMULATION_FACTORY_H
#define PROJECT_SOFT_BODY_SIMULATION_FACTORY_H

#include <memory>

namespace ifx{
class SceneContainer;
}

class SoftBodySimulation;

class SoftBodySimulationFactory {
public:
    SoftBodySimulationFactory();
    ~SoftBodySimulationFactory();

    std::shared_ptr<SoftBodySimulation> Create(
            std::shared_ptr<ifx::SceneContainer> scene);
private:
};


#endif //PROJECT_SOFT_BODY_SIMULATION_FACTORY_H
