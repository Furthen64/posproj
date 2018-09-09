#ifndef SCREENPOS_H
#define SCREENPOS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


#include "CanvasPos.hpp"


/// ScreenPos is a canvaspos with the added offset of the view. Use Screenpos for:
/// * MOUSE

class ScreenPos
{
public:
ScreenPos();
ScreenPos(int,int);
ScreenPos(float,float);
ScreenPos(sf::Vector2f _vecPos);
ScreenPos(sf::Vector2i _vecPos_i);
ScreenPos(ScreenPos *other);


void drawAll(sf::RenderTarget &rt);
void dump(std::string ind);
std::string dumpToString();
ScreenPos *clone();

sf::Vector2f toVecf();
bool isEqual(ScreenPos *other);


void testScreenPos(int debugLevel = 0);
void rotateAroundOrigoNDegCCW(float n);
void rotateAroundOrigoNDegCW(float n);

float y;
float x;

private:
    std::string cn = "ScreenPos.cpp";
};


#endif
