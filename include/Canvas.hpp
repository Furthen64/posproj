#ifndef CANVAS_H
#define CANVAS_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Constants.hpp"


class Canvas
{
public:
    Canvas();
    void drawAll(sf::RenderTarget& rt);

private:
 std::string cn = "Core.cpp";


};




#endif
