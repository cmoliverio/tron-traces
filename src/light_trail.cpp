#include "light_trail.hpp"

LightTrail::LightTrail() {}

LightTrail::LightTrail(Point starting_point, Direction starting_direction)
    : current_point(starting_point),
      trail(std::make_unique<std::vector<Point>>()),
      current_direction(starting_direction),
      current_speed(0.0f)
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
            break;
        case BACKWARD:
            break;
        default:
            // does nothing
            break;
    }
}