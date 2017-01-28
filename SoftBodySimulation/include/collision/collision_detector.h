#ifndef PROJECT_COLLISION_DETECTOR_H
#define PROJECT_COLLISION_DETECTOR_H

#include <memory>

class Particle;
struct Room;

struct CollisionState;

class CollisionDetector {
public:
    CollisionDetector(std::shared_ptr<Room> room);
    ~CollisionDetector();

    std::shared_ptr<Room> room(){return room_;}

    CollisionState ComputeCollisionState(
            std::shared_ptr<Particle> particle);
private:
    bool CheckFloorCollision(std::shared_ptr<Particle> particle);
    bool CheckCeilingCollision(std::shared_ptr<Particle> particle);

    bool CheckLeftWallCollision(std::shared_ptr<Particle> particle);
    bool CheckRightWallCollision(std::shared_ptr<Particle> particle);

    bool CheckFrontWallCollision(std::shared_ptr<Particle> particle);
    bool CheckBackWallCollision(std::shared_ptr<Particle> particle);

    std::shared_ptr<Room> room_;
};


#endif //PROJECT_COLLISION_DETECTOR_H
