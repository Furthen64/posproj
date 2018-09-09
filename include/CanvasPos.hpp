#ifndef CANVASPOS_H
#define CANVASPOS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "ScreenPos.hpp"

#include "../src/Singletons/WindowSingleton.hpp"

// see Canvas.hpp for more information on what the Canvas and its position mean

/// CanvasPos is the main game position class. If you need to render it on the screen , use the ScreenPos class, and the function ScreenPos->getFromCanvasPos()
/// CanvasPos is used for:
/// * GAME LOGIC


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


    void testCanvasPos(int debugLevel = 0); // Unit test

    sf::Vector2f getSfPositionByCpos(CanvasPos *cpos, bool adaptForView=true);

    void rotateAroundOrigoNDegCCW(float n);
    void rotateAroundOrigoNDegCW(float n);

    float y;
    float x;



private:
    std::string cn = "CanvasPos.cpp";
};


#endif
