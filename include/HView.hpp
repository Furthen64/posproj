#ifndef HVIEW_H
#define HVIEW_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class HView
{
public:
    HView();
    HView(sf::Vector2f _a, sf::Vector2f _b);

    void resizeViewToWindow();

    void *getTopLeft();

    void setTopLeft(void *ptr);

    void drawAll(sf::RenderTarget &rt);

private:
    std::string cn = "HView.cpp";

    sf::View *sfView;
    void *topLeft;


};


#endif
