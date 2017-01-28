#ifndef PROJECT_COLLISION_ROOM_FACTORY_H
#define PROJECT_COLLISION_ROOM_FACTORY_H

#include <memory>

namespace ifx{
class GameObject;
}

class Room;

class CollisionRoomFactory {
public:
    CollisionRoomFactory();
    ~CollisionRoomFactory();

    std::shared_ptr<Room> Create();
private:

    std::shared_ptr<ifx::GameObject> CreateFloor();
    std::shared_ptr<ifx::GameObject> CreateCeiling();

    std::shared_ptr<ifx::GameObject> CreateLeftWall();
    std::shared_ptr<ifx::GameObject> CreateRightWall();
    std::shared_ptr<ifx::GameObject> CreateFrontWall();
    std::shared_ptr<ifx::GameObject> CreateBackWall();
};


#endif //PROJECT_COLLISION_ROOM_FACTORY_H
