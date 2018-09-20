#ifndef SLOTPOS_H
#define SLOTPOS_H

#include <SFML/Graphics.hpp>

#include "../src/Singletons/ResourceHolder.hpp"

#include "IsoPos.hpp"
#include "CanvasPos.hpp"


class SlotPos
{
public:
    SlotPos(IsoPos *_isopos);
    SlotPos(CanvasPos *_cpos);
    IsoPos *isopos;
    CanvasPos *cpos;
    void draw( sf::RenderTarget& rt);
    void dump(std::string ind);


private:
void setupSprite();
    int textureID;
    sf::Texture texture;
    sf::IntRect textureSize;
    std::string textureName="SLOTPOS";
    sf::Sprite sprite;
    std::string cn = "SlotPos.cpp";
};

#endif
