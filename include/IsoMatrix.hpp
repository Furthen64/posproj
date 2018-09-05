#ifndef ISOMATRIX_H
#define ISOMATRIX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "LineRect.hpp"
#include "OrMatrix.hpp"
#include "CanvasPos.hpp"
#include "Constants.hpp"

class IsoMatrix
{
public:
    IsoMatrix();
    IsoMatrix(OrMatrix *);
    void drawAll(sf::RenderTarget& rt);
void setTopLeft(int , int );
void setTopLeft(CanvasPos *cpos);
void setMiddleToCpos(CanvasPos *cpos);
void scale2x();
void rotateNDegCCW(float n);


private:
    std::string cn = "IsoMatrix.cpp";
    CanvasPos *topleft;
    OrMatrix *orMat;    // The parent matrix object
    LineRect *lrect;
};




#endif
