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

    void resizeViewToWindow();

    CanvasPos *getTopLeft();

    void setTopLeft(CanvasPos *ptr);

    void drawAll(sf::RenderTarget &rt);

private:
    std::string cn = "HView.cpp";

    sf::View *sfView = nullptr;

    CanvasPos *topLeft = nullptr;


};


#endif
