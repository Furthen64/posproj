#ifndef HRECT_H
#define HRECT_H

#include <iostream>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "CanvasPos.hpp"

class LineRect; // <-- blargh inclusion



class HRect
{

public:

HRect();
HRect(int _sizeY, int _sizeX);
HRect(CanvasPos *topLeft_cpos, CanvasPos *bottomRight_cpos);
HRect(LineRect *lineRect);


void setTopLeft(CanvasPos *topLeft_cpos);
void setTopLeft(int cpos_y, int cpos_x);

int getSize_y();
int getSize_x();


// General functions
bool containsCanvasPos(CanvasPos *cpos);

int nrTiles(); // A tile is 46 x 46 px, and the HRect is 46 x 92 px, that would mean nrTiles = 2

int compare(HRect *other);
int compareAbsStartPoint(HRect *other);
int compareSize(HRect *other);

bool insideXPixles_middle(CanvasPos *point_cpos);
bool insideYPixles_middle(CanvasPos *point_cpos);

HRect *clone();

CanvasPos *topLeft;
CanvasPos *bottomRight;

void drawAll(sf::RenderTarget &rt);

private:

std::string cn = "HRect.cpp";
};

#endif
