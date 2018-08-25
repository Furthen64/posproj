#ifndef SVIEW_H
#define SVIEW_H


#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>


class SView
{
public:
    SView();

    void resizeView(int, int );

private:
    std::string cn = "SView.cpp";

    sf::View *view;


};




#endif
