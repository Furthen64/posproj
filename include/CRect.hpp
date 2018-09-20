#ifndef CRECT_H
#define CRECT_H

#include <iostream>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "CanvasPos.hpp"

class LineRect; // <-- blargh inclusion



class CRect
{

public:

    CRect();
    CRect(int _sizeY, int _sizeX);
    CRect(CanvasPos *topLeft_cpos, CanvasPos *bottomRight_cpos);
    CRect(LineRect *lineRect);

    void setTopLeft(CanvasPos *topLeft_cpos);
    void setTopLeft(int cpos_y, int cpos_x);

    int getSize_y();
    int getSize_x();

    CanvasPos *getMiddle_cpos();


    // General functions

    int nrTiles(); // A tile is 46 x 46 px, and the CRect is 46 x 92 px, that would mean nrTiles = 2

    int compare(CRect *other);
    int compareAbsStartPoint(CRect *other);
    int compareSize(CRect *other);

    bool inside(CanvasPos *cpos);
    bool insideXPixles_middle(CanvasPos *point_cpos);
    bool insideYPixles_middle(CanvasPos *point_cpos);

    CRect *clone();
    void dump();

    CanvasPos *topLeft;
    CanvasPos *bottomRight;

    void drawAll(sf::RenderTarget &rt);

private:

    std::string cn = "CRect.cpp";
};

#endif
