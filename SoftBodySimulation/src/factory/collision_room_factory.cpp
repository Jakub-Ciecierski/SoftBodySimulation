#include "factory/collision_room_factory.h"

#include <graphics/factory/render_object_factory.h>
#include <object/game_object.h>
#include <room.h>

CollisionRoomFactory::CollisionRoomFactory(){}
CollisionRoomFactory::~CollisionRoomFactory(){}

std::shared_ptr<Room> CollisionRoomFactory::Create(){
    auto room = std::shared_ptr<Room>(new Room());

    room->floor = CreateFloor();
    room->ceiling = CreateCeiling();


    room->left_wall = CreateLeftWall();
    room->right_wall = CreateRightWall();

    room->front_wall = CreateFrontWall();
    room->back_wall = CreateBackWall();

    return room;
}

std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateFloor(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}

std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateCeiling(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->rotateTo(glm::vec3(180, 0, 0));
    game_object->moveTo(glm::vec3(0, 10, 0));
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}


std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateLeftWall(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->rotateTo(glm::vec3(90, 0, 0));
    game_object->moveTo(glm::vec3(0, 5, -5));
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}

std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateRightWall(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->rotateTo(glm::vec3(-90, 0, 0));
    game_object->moveTo(glm::vec3(0, 5, 5));
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}

std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateFrontWall(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->rotateTo(glm::vec3(0, 0, 90));
    game_object->moveTo(glm::vec3(5, 5, 0));
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}

std::shared_ptr<ifx::GameObject> CollisionRoomFactory::CreateBackWall(){
    auto game_object = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object->rotateTo(glm::vec3(0, 0, -90));
    game_object->moveTo(glm::vec3(-5, 5, 0));
    game_object->Add(ifx::RenderObjectFactory().CreateFloor());
    return game_object;
}