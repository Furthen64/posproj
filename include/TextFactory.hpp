#ifndef TEXTFACTORY_H
#define TEXTFACTORY_H

#include "../src/Singletons/ResourceHolder.hpp"


// sf::Text is commonly used to display text on screen.
// So I created this class to be able to construct some of the most common format of texts that I want to see,
// like for instance, printing out positions.
//
//              Bus sfml::position(320,100)px
//
// To do this I would call the factory to generate the text with a font setup and everything good to go.
/// Example usage:
///  TextFactory::textForsfmlPosition("Bus sfml::position", 320,100);

class TextFactory
{
public:
    TextFactory();





    static sf::Text *getTextShowingPosition(std::string preStr , int fontSizePx,  float value_y, float value_x, sf::Color sfColor)
    {
        ResourceHolder *res;
        res = res->getInstance();

        std::string fullStr = preStr + " ( ";
        fullStr += std::to_string(value_y);
        fullStr += ", ";
        fullStr += std::to_string(value_x);
        fullStr += ")";
        sf::Text *sftext = new sf::Text(fullStr, *(res->fixedsysFont), fontSizePx);

        sftext->setFillColor(sfColor);

        // Text Style ?
        // sftext->setStyle(sf::Text::Bold | sf::Text::Underlined);

        // Set default position
        sftext->setPosition(0,0);

        return sftext;

    }

    // (--)
    static sf::Text *getText(std::string inputStr, int fontSizePx, sf::Color color)
    {


        ResourceHolder *res;
        res = res->getInstance();

        // What!!??! DPONT DETGE DISTRACTED??? I GET DISTRACTED ALL TEH TIME

        sf::Text *sftext = new sf::Text(inputStr, *(res->fixedsysFont) , fontSizePx);

        sftext->setFillColor(color);

        sftext->setPosition(0,0);

        return sftext;
    }



private:
};





#endif
