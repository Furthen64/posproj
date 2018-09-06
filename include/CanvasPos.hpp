#ifndef CANVASPOS_H
#define CANVASPOS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


// see Canvas.hpp for more information on what the Canvas and its position mean

class CanvasPos
{
public:
    CanvasPos();
CanvasPos(int,int);
CanvasPos(float,float);
CanvasPos(sf::Vector2f _vecPos);
CanvasPos(CanvasPos *other);


void drawAll(sf::RenderTarget &rt);
void dump(std::string ind);
std::string dumpToString();
CanvasPos *clone();
sf::Vector2f getSfVec();
bool isEqual(CanvasPos *other);

// Unit tests
void testCanvasPos(int debugLevel = 0);

void rotateAroundOrigoNDegCCW(float n);
void rotateAroundOrigoNDegCW(float n);

    float y;
    float x;



private:
    std::string cn = "CanvasPos.cpp";
};


#endif
