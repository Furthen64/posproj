#include "HRect.hpp"


#include "LineRect.hpp"
////////////////////////////////////////////
// Constructors


HRect::HRect()
{
    // Default size default position
    topLeft = new CanvasPos(0,0);
    bottomRight = new CanvasPos(46,46);
}

// Given a size, create an hrect with default position of topleft = (0,0)
HRect::HRect(int _sizeY, int _sizeX)
{
    topLeft = new CanvasPos(0,0);

    bottomRight = new CanvasPos(_sizeY, _sizeX);
}


// TopLeft and BottomRight defines a rectangle.
HRect::HRect(CanvasPos *_topLeft_cpos, CanvasPos *_bottomRight_cpos)
{
    topLeft = _topLeft_cpos;

    bottomRight = _bottomRight_cpos;
}


HRect::HRect(LineRect *lineRect)
{
    // find out the most top point (lowest y-value)
    CanvasPos *top = lineRect->getTop_cpos();
    // find out the most left point .. and so on.
    CanvasPos *left = lineRect->getLeft_cpos();
    CanvasPos *right = lineRect->getRight_cpos();
    CanvasPos *bottom = lineRect->getBottom_cpos();


    // Now make a square out of these coordinates
    topLeft = new CanvasPos( top->y, left->x);
    bottomRight = new CanvasPos( bottom->y, right->x);
}


////////////////////////////////////////////







int HRect::getSize_y()
{
    return (bottomRight->y - topLeft->y);
}

int HRect::getSize_x()
{
    return (bottomRight->x - topLeft->x);
}


CanvasPos *HRect::getMiddle_cpos()
{

    CanvasPos *_cpos = new CanvasPos(0,0);

    _cpos->x = topLeft->x + (getSize_x()/2);
    _cpos->y = topLeft->y + (getSize_y()/2);

    return _cpos;

}




// Sets topleft position,
void HRect::setTopLeft(int cpos_y, int cpos_x)
{
    int size_y = getSize_y();
    int size_x = getSize_x();

    topLeft = new CanvasPos(cpos_y, cpos_x);

    bottomRight = new CanvasPos( cpos_y + size_y,
                                 cpos_x + size_x );

}


void HRect::setTopLeft(CanvasPos *topLeft_cpos)
{
    int size_y = getSize_y();
    int size_x = getSize_x();

    topLeft = topLeft_cpos;

    bottomRight = new CanvasPos( topLeft->y + size_y,
                                 topLeft->x + size_x );

}


void HRect::drawAll(sf::RenderTarget &rt)
{
    sf::RectangleShape rect(sf::Vector2f(getSize_x(), getSize_y()));

    rect.setPosition( topLeft->getSfVec());

    rect.setOutlineColor(sf::Color(25,125,125));
    rect.setOutlineThickness(1.0f);
    rect.setFillColor(sf::Color(0,0,0,0));  // Transparent fill?


    rt.draw(rect);

}













