#include "ScreenPos.hpp"

#include <assert.h>

#include "Utilities/Utils.hpp"
#include "HView.hpp"




ScreenPos::ScreenPos()
{
    y = 0;
    x = 0;
}


ScreenPos::ScreenPos(float _y,float _x)
{
    y = _y;
    x = _x;

}

ScreenPos::ScreenPos(int _y, int _x)
{
    y = (int)_y;
    x = (int)_x;
}

ScreenPos::ScreenPos(sf::Vector2f _vecPos)
{
    y = _vecPos.y;
    x = _vecPos.x;
}

ScreenPos::ScreenPos(sf::Vector2i _vecPos_i)
{

    y = (float)_vecPos_i.y;
    x = (float)_vecPos_i.x;

}



ScreenPos::ScreenPos(ScreenPos *other)
{
    y = other->y;
    x = other->x;
}



void ScreenPos::drawAll(sf::RenderTarget &rt)
{
    sf::RectangleShape rect(sf::Vector2f(5.0f,5.0f));   // Make a 1x1 px square
    rect.setPosition(toVecf().x-3, toVecf().y-3);
    rt.draw(rect);
}


sf::Vector2f ScreenPos::toVecf()
{
    return sf::Vector2f(x,y);
}

void ScreenPos::dump(std::string ind)
{
    std::cout << ind << "(" << (int)y << ", " << x << ")        float(" << y << ", " << x << ")\n";
}


std::string ScreenPos::dumpToString()
{
    std::string str = "(";
    str += std::to_string((int)y);
    str += ", ";
    str += std::to_string((int)x);
    str += ")";
    return str;
}

ScreenPos *ScreenPos::clone()
{
    return new ScreenPos(y,x);
}

bool ScreenPos::isEqual(ScreenPos *other)
{
    if( ( (int)other->y == (int)this->y) &&
        ( (int)other->x == (int)this->x) ) {
            return true;
        }


    return false;

}






void ScreenPos::testScreenPos(int debugLevel)
{
 //   std::cout << "testScreenPos()------------------------------------\n";

    ScreenPos *a = new ScreenPos();
    ScreenPos *b = new ScreenPos();

    assert(a != nullptr);
    assert(b != nullptr);

    ScreenPos *c = new ScreenPos(25,100);
    ScreenPos *d = new ScreenPos(25,100);

    assert(c->isEqual(d));

    ScreenPos *c2 = new ScreenPos(25,101);
    ScreenPos *d2 = new ScreenPos(100,25);

    assert(!c->isEqual(c2));
    assert(!d->isEqual(d2));
}




void ScreenPos::rotateAroundOrigoNDegCCW(float n)
{
    // Store away current value
    float oldY = y;
    float oldX = x;

    y = rotateCCW_y(oldY, oldX, n);
    x = rotateCCW_x(oldY, oldX, n);
}

void ScreenPos::rotateAroundOrigoNDegCW(float n)
{
    // Store away current value
    float oldY = y;
    float oldX = x;

    y = rotateCW_y(oldY, oldX, n);
    x = rotateCW_x(oldY, oldX, n);
}



















