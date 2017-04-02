#include "Direction.hpp"

Direction::Direction(int m):mDirection(m){};

Direction Direction::North(){return Direction(0);}
Direction Direction::East(){return Direction(1);}
Direction Direction::South(){return Direction(2);}
Direction Direction::West(){return Direction(3);}

int Direction::GetDirection() const
{
    return mDirection;
}
