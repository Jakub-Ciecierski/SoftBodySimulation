#include "example_gui.h"

#include <engine_gui/factory/engine_gui_factory.h>
#include <engine_gui/engine_gui.h>
#include <gui/imgui/imgui.h>
#include <physics/bullet_extensions/btFractureDynamicsWorld.h>
#include <physics/simulations/bullet_physics_simulation.h>
#include <soft_body_simulation.h>
#include <particle_system/particle_system_distorter.h>
#include <particle_system/particle_system.h>

ExampleGUI::ExampleGUI(GLFWwindow* window,
                       std::shared_ptr<ifx::SceneContainer> scene,
                       std::shared_ptr<SoftBodySimulation> simulation,
                       std::shared_ptr<ifx::PhysicsSimulation> physics_simulation) :
        ifx::GUI(window),
        simulation_(simulation){
    engine_gui_ = ifx::EngineGUIFactory().CreateEngineGUI(scene,
                                                          physics_simulation);
}
ExampleGUI::~ExampleGUI(){}

void ExampleGUI::Render(){
    NewFrame();

    engine_gui_->Render();

    ImGui::Begin("Soft Body Simulation");
    RenderWindow();
    ImGui::End();

    ImGui::Render();
}

void ExampleGUI::RenderWindow(){
    RenderSimulationInfo();
    RenderVelocityDistortion();
}

void ExampleGUI::RenderSimulationInfo(){
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Time: %.2f [s]", simulation_->time_data().total_time);

    if (ImGui::Button("Reset")) {
        simulation_->SetRunning(true);
        simulation_->Reset();
    }
    ImGui::SameLine();

    std::string play_button_text;
    if (simulation_->IsRunning())
        play_button_text = "Pause";
    else
        play_button_text = "Play";

    if (ImGui::Button(play_button_text.c_str())) {
        simulation_->SetRunning(!simulation_->IsRunning());
    }
}

void ExampleGUI::RenderVelocityDistortion(){
    if(ImGui::Button("Distort velocity")){
        ParticleSystemDistorter distorter;
        distorter.DistortParticlesVelocity(simulation_->particle_system());
    }

}