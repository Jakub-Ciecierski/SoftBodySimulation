#ifndef PROJECT_EXAMPLE_GUI_H
#define PROJECT_EXAMPLE_GUI_H

#include "gui/gui.h"

#include <memory>

class SoftBodySimulation;

namespace ifx{
class EngineGUI;
class SceneContainer;
class PhysicsSimulation;
}

class ExampleGUI : public ifx::GUI{
public:

    ExampleGUI(GLFWwindow* window,
               std::shared_ptr<ifx::SceneContainer> scene,
               std::shared_ptr<SoftBodySimulation> hodograph_simulation,
               std::shared_ptr<ifx::PhysicsSimulation> physics_simulation);
    ~ExampleGUI();

    virtual void Render() override;
private:
    void RenderWindow();
    void RenderSimulationInfo();
    void RenderVelocityDistortion();

    void RenderParameters();
    void RenderDampingParameter();
    void RenderSpringCoefficient1();
    void RenderSpringCoefficient2();
    void RenderMass();

    std::shared_ptr<ifx::EngineGUI> engine_gui_;
    std::shared_ptr<SoftBodySimulation> simulation_;

};


#endif //PROJECT_EXAMPLE_GUI_H
