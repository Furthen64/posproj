#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "SFML/Graphics.hpp"
#include "IsoPos.hpp"


/// Locomotive
///
/// Hey!
///
/// If you need to work on Locomotive again, please take a look at Bus class for its direction and speed and stuffs.
///
class Locomotive
{
public:

    Locomotive();

    void draw( sf::RenderTarget& rt);

private:
    float speed = 16.0f;  // move 100 px per second
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
