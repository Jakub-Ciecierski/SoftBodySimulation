#ifndef PROJECT_COLLISION_STATE_H
#define PROJECT_COLLISION_STATE_H

/**
 * Set of booleans linked to each wall, indicating if collision was detected
 * with that wall.
 */
struct CollisionState{
    bool floor = false;
    bool ceiling = false;
    bool left_wall = false;
    bool right_wall = false;
    bool front_wall = false;
    bool back_wall = false;

    bool FoundCollision(){
        return floor || ceiling
               || left_wall || right_wall
               || front_wall || back_wall;
    }
};



#endif //PROJECT_COLLISION_STATE_H
