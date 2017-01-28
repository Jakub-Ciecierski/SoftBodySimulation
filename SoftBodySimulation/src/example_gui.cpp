#include "example_gui.h"

#include <engine_gui/factory/engine_gui_factory.h>
#include <engine_gui/engine_gui.h>
#include <engine_gui/views/scene_view.h>

#include <gui/imgui/imgui.h>
#include <physics/bullet_extensions/btFractureDynamicsWorld.h>
#include <physics/simulations/bullet_physics_simulation.h>
#include <soft_body_simulation.h>
#include <particle_system/particle_system_distorter.h>
#include <particle_system/particle_system.h>
#include <particle_system/particle.h>
#include <particle_system/spring/spring_constraint.h>
#include <control_box.h>
#include <game/scene_container.h>
#include <game/game_loop.h>
#include <iostream>
#include <factory/particle_system_factory.h>
#include <factory/soft_body_simulation_factory.h>
#include <collision/collision_handler.h>
#include <bezier_cube.h>

ExampleGUI::ExampleGUI(GLFWwindow* window,
                       std::shared_ptr<ifx::SceneContainer> scene,
                       std::shared_ptr<SoftBodySimulation> simulation,
                       std::shared_ptr<ifx::PhysicsSimulation>
                       physics_simulation,
                       std::shared_ptr<ifx::GameLoop> game_loop) :
        ifx::GUI(window),
        simulation_(simulation),
        scene_(scene),
        game_loop_(game_loop){
    engine_gui_ = ifx::EngineGUIFactory().CreateEngineGUI(scene,
                                                          physics_simulation);
    Reset();
    SelectControlBox();
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
    if(ImGui::TreeNode("Simualtion")){
        RenderSimulationInfo();
        ImGui::TreePop();
    }

    if(ImGui::TreeNode("Parameters")){
        RenderSelectControlBox();
        RenderVelocityDistortion();
        RenderParameters();
        ImGui::TreePop();
    }

    if(ImGui::TreeNode("Render")){
        RenderRenderOptions();
        ImGui::TreePop();
    }
}

void ExampleGUI::RenderSimulationInfo(){
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Time: %.2f [s]", simulation_->time_data().total_time);

    if (ImGui::Button("Reset")) {
        simulation_->SetRunning(true);
        simulation_->Reset();
        Reset();
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

void ExampleGUI::RenderSelectControlBox(){
    if(ImGui::Button("Select Control Box")){
        SelectControlBox();
    }
}

void ExampleGUI::RenderParameters(){
    RenderDampingParameter();
    RenderSpringCoefficient1();
    RenderSpringCoefficient2();
    RenderMass();
    RenderGravity();
    RenderRestitution();
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

void ExampleGUI::RenderGravity(){
    static float raw[3];
    const glm::vec3& g = simulation_->particle_system()->gravity_force();

    raw[0] = g.x;
    raw[1] = g.y;
    raw[2] = g.z;

    ImGui::SliderFloat3("Gravity", raw, -10, 10);
    simulation_->particle_system()->gravity_force(
            glm::vec3(raw[0], raw[1], raw[2]));
}

void ExampleGUI::RenderRestitution(){
    ImGui::SliderFloat("Restitution",
                       simulation_->particle_system()->
                               collision_handler()->restitution(), 0, 1);
}

void ExampleGUI::RenderRenderOptions(){
    RenderShowConstraints();
    RenderShowBezierCube();
    RenderShowParticles();
}

void ExampleGUI::RenderShowConstraints(){
    static bool v;
    v = simulation_->particle_system()->draw_constraints();
    if(ImGui::Checkbox("Show Constraints", &v)){
        simulation_->particle_system()->draw_constraints(v);
    }
}

void ExampleGUI::RenderShowBezierCube(){
    static bool v;
    v = simulation_->bezier_cube()->show();
    if(ImGui::Checkbox("Show Bezier Cube", &v)){
        simulation_->bezier_cube()->show(v);
    }
}

void ExampleGUI::RenderShowParticles(){
    static bool v;
    v = simulation_->particle_system()->draw_particles();
    if(ImGui::Checkbox("Show Particles", &v)){
        simulation_->particle_system()->draw_particles(v);
    }
}

void ExampleGUI::Reset(){
    if(simulation_ && simulation_->control_box()->game_object())
        scene_->Remove(simulation_->control_box()->game_object());

    auto simulation = SoftBodySimulationFactory().Create(scene_);
    ParticleSystemFactory().Init(simulation->particle_system(),
                                 simulation->control_box());
    scene_->Add(simulation->control_box()->game_object());

    if(simulation_)
        game_loop_->RemoveSimulation(simulation_);

    simulation_ = simulation;
    game_loop_->AddSimulation(simulation);

    SelectControlBox();
}

void ExampleGUI::SelectControlBox(){
    if(simulation_->control_box()->game_object()){
        engine_gui_->scene_view()->SetSelectedGameObject(
                simulation_->control_box()->game_object());
    }
}