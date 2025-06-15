#ifndef LIGHT_TRAIL_H
#define LIGHT_TRAIL_H

#include <vector>
#include <memory>
#include <array>

typedef std::array<float, 3> Point; // x, y, z

enum Direction {
        UP,
        DOWN,
        // LEFT, <-- LightTrails can only move left to right
        RIGHT,
        FORWARD,
        BACKWARD
};

class LightTrail {
public:
    LightTrail();
    LightTrail(Point starting_point, Direction starting_direction);
    ~LightTrail();

    Point current_point;
    std::unique_ptr<std::vector<Point>> trail;
    Direction current_direction;
    float current_speed;
    
    void turn();
    void move();
    
};

#endif // LIGHT_TRAIL_H