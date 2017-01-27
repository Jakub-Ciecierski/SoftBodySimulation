#include <game/game_loop.h>
#include <game/factory/game_loop_factory.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/rendering/renderer.h>
#include <game/factory/game_factory.h>
#include <game/game.h>
#include <game/scene_container.h>
#include <object/game_object.h>
#include <graphics/factory/scene_factory.h>
#include <graphics/lighting/light_source.h>
#include <graphics/lighting/types/light_directional.h>
#include <graphics/lighting/types/light_spotlight.h>

#include <graphics/rendering/camera/camera.h>
#include <engine_gui/factory/engine_gui_factory.h>
#include <graphics/rendering/renderer.h>
#include <engine_gui/engine_gui.h>
#include <example_gui.h>

#include <soft_body_simulation.h>
#include <control_box.h>
#include <factory/soft_body_simulation_factory.h>
#include <factory/particle_system_factory.h>

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight();
std::shared_ptr<ifx::LightSpotlight> CreateSpotLight();

std::shared_ptr<ifx::GameObject> CreateGameObjectFloor();
std::shared_ptr<ifx::GameObject> CreateGameObjectLight();

std::shared_ptr<SoftBodySimulation> CreateSoftBodySimulation(
        std::shared_ptr<ifx::SceneContainer> scene);

std::shared_ptr<ifx::LightDirectional> CreateDirectionalLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightDirectional>(
            new ifx::LightDirectional(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));
    light_source->rotateTo(glm::vec3(322, 295, 0));

    return light_source;
}

std::shared_ptr<ifx::LightSpotlight> CreateSpotLight(){
    ifx::LightParams light;

    light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    light.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    auto light_source = std::shared_ptr<ifx::LightSpotlight>(
            new ifx::LightSpotlight(light));
    light_source->rotateTo(glm::vec3(0, 270, 0));

    return light_source;
}


std::shared_ptr<ifx::GameObject> CreateGameObjectFloor(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    game_object->Add(ifx::RenderObjectFactory().CreateFloor());

    return game_object;
}

std::shared_ptr<ifx::GameObject> CreateGameObjectLight(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto lamp = ifx::RenderObjectFactory().CreateLampObject();

    game_object->Add(std::move(lamp));
    game_object->Add(CreateSpotLight());
    game_object->Add(CreateDirectionalLight());
    game_object->moveTo(glm::vec3(0.0f, 7.0f, 0.0f));

    return game_object;
}

std::shared_ptr<SoftBodySimulation> CreateSoftBodySimulation(
        std::shared_ptr<ifx::SceneContainer> scene){
    auto simulation = SoftBodySimulationFactory().Create(scene);
    scene->Add(simulation->control_box()->game_object());

    ParticleSystemFactory().Init(simulation->particle_system(),
                                 simulation->control_box());

    return simulation;
}

int main() {
    auto game_factory
            = std::shared_ptr<ifx::GameFactory>(new ifx::GameFactory());
    auto game = game_factory->Create();

    auto game_object1 = CreateGameObjectFloor();
    auto game_object2 = CreateGameObjectLight();

    auto game_object3 = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object3->Add(
            ifx::SceneFactory().CreateCamera(game->game_loop()->renderer()->window()));
    game_object3->moveTo(glm::vec3(-7, 2, 0));

    game->scene()->Add(game_object1);
    game->scene()->Add(game_object2);
    game->scene()->Add(game_object3);

    auto simulation = CreateSoftBodySimulation(game->scene());

    auto gui = std::shared_ptr<ExampleGUI>(
            new ExampleGUI(
                    game->game_loop()->renderer()->window()->getHandle(),
                    game->scene(),
                    simulation,
                    game->game_loop()->physics_simulation()));
    game->game_loop()->renderer()->SetGUI(gui);

    game->game_loop()->AddSimulation(simulation);

    game->Start();
}
