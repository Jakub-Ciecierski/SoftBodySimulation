#include "factory/control_box_factory.h"

#include <control_box.h>

#include <object/game_object.h>
#include <graphics/factory/render_object_factory.h>
#include <graphics/model/material.h>
#include <graphics/model/model.h>
#include <graphics/factory/texture_factory.h>

ControlBoxFactory::ControlBoxFactory(){

}

ControlBoxFactory::~ControlBoxFactory(){

}

std::shared_ptr<ControlBox> ControlBoxFactory::CreateControlBox(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    auto render_object = ifx::RenderObjectFactory().CreateCube();
    auto material = std::shared_ptr<ifx::Material>(new ifx::Material());
    material->diffuse = ifx::TextureFactory().CreateSolidColorTexture(
            glm::vec3(255,0,0), ifx::TextureTypes::DIFFUSE);
    material->specular = ifx::TextureFactory().CreateSolidColorTexture(
            glm::vec3(255,0,0), ifx::TextureTypes::SPECULAR);

    render_object->models()[0]->getMesh(0)->material(material);
    render_object->models()[0]->getMesh(0)->polygon_mode
            (ifx::PolygonMode::LINE);

    game_object->Add(render_object);
    float a = 2;
    game_object->moveTo(glm::vec3(0, 2*a, 0));
    auto control_box = std::shared_ptr<ControlBox>(new ControlBox(game_object,
                                                                  a));
    return control_box;
}