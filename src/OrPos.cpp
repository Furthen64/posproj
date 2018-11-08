#include "OrPos.hpp"
// Orthogonal Position

OrPos::OrPos()
{
    y = 0;
    x = 0;
}

OrPos::OrPos(float _y, float _x)
{
    y = _y;
    x = _x;
}


void OrPos::dump(std::string ind)
{
    std::cout << ind << "(" << std::to_string(y) << ", " << std::to_string(x) << ")\n";
}
