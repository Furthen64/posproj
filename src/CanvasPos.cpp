#include "CanvasPos.hpp"

#include <assert.h>

#include "Utilities/Utils.hpp"
#include "HView.hpp"

CanvasPos::CanvasPos()
{
    y = 0;
    x = 0;
}


CanvasPos::CanvasPos(float _y,float _x)
{
    y = _y;
    x = _x;

}

CanvasPos::CanvasPos(int _y, int _x)
{
    y = (int)_y;
    x = (int)_x;
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
    sf::RectangleShape rect(sf::Vector2f(5.0f,5.0f));   // Make a 1x1 px square
    rect.setPosition(getSfVec().x-3, getSfVec().y-3);
    rt.draw(rect);
}


sf::Vector2f CanvasPos::getSfVec()
{
    return sf::Vector2f(x,y);
}

void CanvasPos::dump(std::string ind)
{
    std::cout << ind << "(" << (int)y << ", " << x << ")        float(" << y << ", " << x << ")\n";
}


std::string CanvasPos::dumpToString()
{
    std::string str = "(";
    str += std::to_string((int)y);
    str += ", ";
    str += std::to_string((int)x);
    str += ")";
    return str;
}

CanvasPos *CanvasPos::clone()
{
    return new CanvasPos(y,x);
}

bool CanvasPos::isEqual(CanvasPos *other)
{
    if( ( (int)other->y == (int)this->y) &&
        ( (int)other->x == (int)this->x) ) {
            return true;
        }


    return false;

}



void CanvasPos::testCanvasPos(int debugLevel)
{
 //   std::cout << "testCanvasPos()------------------------------------\n";

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
}




void CanvasPos::rotateAroundOrigoNDegCCW(float n)
{
    // Store away current value
    float oldY = y;
    float oldX = x;

    y = rotateCCW_y(oldY, oldX, n);
    x = rotateCCW_x(oldY, oldX, n);
}

void CanvasPos::rotateAroundOrigoNDegCW(float n)
{
    // Store away current value
    float oldY = y;
    float oldX = x;

    y = rotateCW_y(oldY, oldX, n);
    x = rotateCW_x(oldY, oldX, n);
}


sf::Vector2f CanvasPos::getSfPositionByCpos(CanvasPos *cpos, bool adaptForView)
{
    WindowSingleton *win;
    win = win->getInstance();
    HView *hview = win->hview;

    if(adaptForView) {
        return sf::Vector2f(hview->getTopLeft_x() + cpos->x, hview->getTopLeft_y() + cpos->y);
    }

    return sf::Vector2f(cpos->x, cpos->y);
}


















