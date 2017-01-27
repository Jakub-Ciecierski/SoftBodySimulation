#include "example_gui.h"

#include <engine_gui/factory/engine_gui_factory.h>
#include <engine_gui/engine_gui.h>
#include <gui/imgui/imgui.h>
#include <physics/bullet_extensions/btFractureDynamicsWorld.h>
#include <physics/simulations/bullet_physics_simulation.h>
#include <soft_body_simulation.h>
#include <particle_system/particle_system_distorter.h>
#include <particle_system/particle_system.h>
#include <particle_system/particle.h>
#include <particle_system/spring/spring_constraint.h>
#include <control_box.h>

#include <iostream>

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
    RenderParameters();
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

void ExampleGUI::RenderParameters(){
    RenderDampingParameter();
    RenderSpringCoefficient1();
    RenderSpringCoefficient2();
    RenderMass();
}

void ExampleGUI::RenderDampingParameter(){
    ImGui::SliderFloat("Damping (k)", simulation_->particle_system()->damping(), 0.0, 100);
}

void ExampleGUI::RenderSpringCoefficient1(){
    auto& constraints = simulation_->particle_system()->constraints();
    static float c1 = 0.1;
    if(constraints.size() > 0){
        c1 = *(std::static_pointer_cast<SpringConstraint>(constraints[0])->spring_coefficient());
    }

    if(ImGui::SliderFloat("Spring Coefficient 1 (c1)", &c1, 0.1, 100)){
        for(auto& constraint : constraints){
            auto spring_constraint = std::static_pointer_cast<SpringConstraint>(constraint);
            if(!spring_constraint->is_control_box()){
                spring_constraint->spring_coefficient(c1);
            }
        }
    }
}

void ExampleGUI::RenderSpringCoefficient2(){
    auto& constraints = simulation_->control_box()->constraints();
    static float c2 = 0.1;
    if(constraints.size() > 0){
        c2 = *(std::static_pointer_cast<SpringConstraint>(constraints[0])->spring_coefficient());
    }

    if(ImGui::SliderFloat("Spring Coefficient 2 (c2)", &c2, 0.1, 100)) {
        for (auto &constraint : constraints) {
            auto spring_constraint = std::static_pointer_cast<SpringConstraint>(constraint);
            if (spring_constraint->is_control_box()) {
                spring_constraint->spring_coefficient(c2);
            }
        }
    }
}

void ExampleGUI::RenderMass(){
    auto& particles = simulation_->particle_system()->particles();

    static float mass = 1.0f;
    if(particles.size() > 0)
        mass = *particles[0]->mass();

    if(ImGui::SliderFloat("Mass", &mass, 0.1, 100)) {
        for (auto& particle : particles) {
            particle->mass(mass);
        }
    }
}