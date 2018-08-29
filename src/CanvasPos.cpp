#include "CanvasPos.hpp"

#include <assert.h>

CanvasPos::CanvasPos()
{
    y = 0;
    x = 0;
}


CanvasPos::CanvasPos(int _y, int _x)
{
    y = _y;
    x = _x;
}

CanvasPos::CanvasPos(sf::Vector2f _vecPos)
{
    y = _vecPos.y;
    x = _vecPos.x;
}


CanvasPos::CanvasPos(CanvasPos *other)
{
    y = other->y;
    x = other->x;
}

void CanvasPos::drawAll(sf::RenderTarget &rt)
{
    sf::RectangleShape rect(sf::Vector2f(1.0f,1.0f));   // Make a 1x1 px square
    rect.setPosition(sf::Vector2f(y,x));
    rt.draw(rect);
}


void CanvasPos::dump(std::string ind)
{
    std::cout << ind << "(" << y << ", " << x << ")\n";
}


std::string CanvasPos::dumpToString()
{
    std::string str = "(";
    str += std::to_string(y);
    str += ", ";
    str += std::to_string(x);
    str += ")";
    return str;
}

CanvasPos *CanvasPos::clone()
{
    return new CanvasPos(y,x);
}

bool CanvasPos::isEqual(CanvasPos *other)
{
    if( (other->y == this->y) &&
        (other->x == this->x) ) {
            return true;
        }


    return false;

}



bool CanvasPos::testCanvasPos(int debugLevel)
{

    int intRet;
    std::cout << "testCanvasPos()------------------------------------\n";

    CanvasPos *a = new CanvasPos();
    CanvasPos *b = new CanvasPos();

    assert(a != nullptr);
    assert(b != nullptr);

    CanvasPos *c = new CanvasPos(25,100);
    CanvasPos *d = new CanvasPos(25,100);

    assert(c->isEqual(d));

    CanvasPos *c2 = new CanvasPos(25,101);
    CanvasPos *d2 = new CanvasPos(100,25);

    assert(!c->isEqual(c2));
    assert(!d->isEqual(d2));

    return intRet;
}
























