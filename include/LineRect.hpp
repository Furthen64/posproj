#ifndef LINERECT_H
#define LINERECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "HRect.hpp" // <-- "CanvasPos.hpp"


/// A rectangle made up of 4 lines.
/// This allows for easy rotation, scaling and squashing while still knowing each corners position.

class LineRect
{
public:
    LineRect();
    LineRect(CanvasPos *, CanvasPos *, CanvasPos *, CanvasPos *);

void drawAll(sf::RenderTarget &rt);
void moveToOrigo();
void moveBack();

float getSize_y();
float getSize_x();

void scale_y(float );
void scale_x(float );

    void setTopLeft(CanvasPos *_topleft);

    void recalcBoundingBox();   // Run this every time you change any of the positions

    CanvasPos *getTop_cpos();       // find the most top point .. and so on
    CanvasPos *getLeft_cpos();
    CanvasPos *getRight_cpos();
    CanvasPos *getBottom_cpos();
    CanvasPos *getMiddle_cpos();


CanvasPos *getTopLeft();


void moveByMiddle(CanvasPos *_cpos);


    void rotateAllPointsNDegCCW(float n);
    void rotateAllPointsNDegCW(float n);

    // Vars
    CanvasPos *A = nullptr;
    CanvasPos *B = nullptr;
    CanvasPos *C = nullptr;
    CanvasPos *D = nullptr;


private:
    CanvasPos *prevPos = nullptr;   // Used by moveToOrigo and moveBack
    HRect *boundingBox = nullptr;   // Used to know topleft corner
    std::string cn = "LineRect.cpp";
};


#endif
