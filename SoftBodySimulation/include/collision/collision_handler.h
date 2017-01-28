#ifndef PROJECT_COLLISION_HANDLER_H
#define PROJECT_COLLISION_HANDLER_H

#include <memory>

struct Room;
class Particle;
struct CollisionState;

class CollisionHandler {
public:
    CollisionHandler(std::shared_ptr<Room> room);
    ~CollisionHandler();

    float* restitution(){return &restitution_;}

    void HandleCollision(std::shared_ptr<Particle> particle,
                         const CollisionState& collision_state);
private:
    void HandleFloorCeilingCollision(std::shared_ptr<Particle> particle);
    void HandleLeftRightWallCollision(std::shared_ptr<Particle> particle);
    void HandleFrontBackWallCollision(std::shared_ptr<Particle> particle);

    float restitution_;

    std::shared_ptr<Room> room_;
};


#endif //PROJECT_COLLISION_HANDLER_H
