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
    void setTopLeft(CanvasPos *);
    void setPosByNewMiddle(CanvasPos *);

    void moveToOrigo();
void moveByTopLeftSaveMiddle(CanvasPos *);
    void moveBack();

void scale_y(float scaleFactor);
    void rotateNDegCCW(float n);
    void rotateNDegCW(float n);

    CanvasPos *getMiddle_cpos();
    CanvasPos *getTopLeft_cpos();



private:
    std::string cn = "IsoMatrix.cpp";
    CanvasPos *topleft;
    CanvasPos *prev_cpos;
    OrMatrix *orMat;    // The parent matrix object
    LineRect *lrect;
};




#endif
