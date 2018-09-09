#ifndef HVIEW_H
#define HVIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "CanvasPos.hpp"

class HView
{

public:

    HView();
    HView(sf::Vector2f _a, sf::Vector2f _b);


    int getTopLeft_y();
    int getTopLeft_x();

std::string toString();

void resizeViewToWindow();
void updateWindowView();
void setTopLeft(CanvasPos *ptr);    // Updates the Window view with this new position
void setTopLeft(int y, int x);      // Updates the Window view with this new position
void drawAll(sf::RenderTarget &rt);


    void moveView(float relativeY, float relativeX);
    void dump();

private:
    std::string cn = "HView.cpp";

    sf::View *sfView = nullptr;

    CanvasPos *topLeft = nullptr;           // This is the reason why I created this class. Whenever you change this topleft, the sfml view is updated.
};


#endif
