#ifndef CANVAS_H
#define CANVAS_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "HView.hpp"
#include "Constants.hpp"



/// The Canvas is the space where everything is drawn.
/// It would help to look at "canvas.png" in the Docs/ to get a proper understanding on what it is in relation to OrMatrix and View etc.
///
/// We don't want the canvas to be in the negative x and y space so we have boundaries
/// that see to it that we only do things in positive space.

/// The canvas has the sf::View object which controls what the user is looking at, at the moment.
/// So when user clicks somewhere in the game, it is within that view.
/// The topleft corner of the view is then the offset to what becomes the "clicked mouse position".
///
/// Hope that makes sense!


class Canvas
{
public:
    Canvas();
    void drawAll(sf::RenderTarget& rt);
    HView *getHView();


private:
    std::string cn = "Core.cpp";
    HView *hview = nullptr;             // Wrapper for the sf::View class, just so I can work more easily with it, adding helper members like "topLeft"



};




#endif
