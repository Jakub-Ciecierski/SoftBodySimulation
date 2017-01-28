#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include <memory>
#include <object/game_object.h>

struct Room {
    std::shared_ptr<ifx::GameObject> floor;
    std::shared_ptr<ifx::GameObject> ceiling;

    std::shared_ptr<ifx::GameObject> left_wall;
    std::shared_ptr<ifx::GameObject> right_wall;

    std::shared_ptr<ifx::GameObject> front_wall;
    std::shared_ptr<ifx::GameObject> back_wall;
};


#endif //PROJECT_ROOM_H
