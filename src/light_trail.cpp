#include "light_trail.hpp"

#include <cmath>

LightTrail::LightTrail() {}

LightTrail::LightTrail(Point starting_point, Direction starting_direction)
    : current_point(starting_point),
      trail(std::make_unique<std::vector<Point>>()),
      current_direction(starting_direction),
      current_speed(0.001f)
{
    this->trail->push_back(starting_point);
}

LightTrail::~LightTrail() 
{
}

void LightTrail::turn()
{

}

void LightTrail::move() 
{
    Point old_point = current_point;
    
    switch (this->current_direction) {
        case UP:
            this->current_point[1] += current_speed;
            break;
        case DOWN:
            this->current_point[1] -= current_speed;
            break;
        case RIGHT:
            this->current_point[0] += current_speed;
            break;
        case FORWARD:
            this->current_point[2] += current_speed;
            break;
        case BACKWARD:
            this->current_point[2] -= current_speed;
            break;
        default:
            // does nothing
            break;
    }

    // Only add a new point if we've moved a significant distance
    // This prevents too many points from being added
    float dx = current_point[0] - old_point[0];
    float dy = current_point[1] - old_point[1];
    float dz = current_point[2] - old_point[2];
    float distance = sqrt(dx*dx + dy*dy + dz*dz);
    
    if (distance > 0.005f) { // Minimum distance threshold
        this->trail->push_back(current_point);
        
        // Optionally limit trail length to prevent memory issues
        if (this->trail->size() > 1000) {
            this->trail->erase(this->trail->begin());
        }
    }
}