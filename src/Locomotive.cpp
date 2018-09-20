#include "Locomotive.hpp"

#include "Utilities/Utils.hpp"

///
/// Locomotive
///
/// Has nothing. Needs everything. Very old code! // 2018-02 I think

Locomotive::Locomotive()
{

    texture.loadFromFile(getFullUri("data\\textures\\LOCOMOTIVE.png"));
    sprite = sf::Sprite(texture);
    sprite.setTextureRect( {0,0,32,32});
}



void Locomotive::draw( sf::RenderTarget& rt)
{
}

