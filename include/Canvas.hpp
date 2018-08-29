#ifndef CANVAS_H
#define CANVAS_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "HView.hpp"
#include "Constants.hpp"


// It would help to look at "canvas.png" in the Docs/ to get a proper understanding on what it is in relation to OrMatrix and View etc.


/// The Canvas is the space where everything is drawn.
/// The Canvas is from 0,0 to inf,inf px.
///
/// How about the Window?
/// The Window size , for instance 1024 x 768 control the size of the view. They are exactly the same size.
///
/// How about the View then?
/// The sfml::View or the wrapper class HView can only move within the boundaries of the Canvas.
///
///




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
