#include "SlotPos.hpp"

#include "HView.hpp"


SlotPos::SlotPos(CanvasPos *_hpos)
{

}

void SlotPos::setupSprite()
{

    if(textureName == "") {
        std::cout << "ERROR " << cn << " Could not create block with empty texturename=" << textureName << "\"!\n";
        return ;
    }


    // Apply texture
    ResourceHolder *res;
    res = res->getInstance();

    res->applyTexture(textureName, &texture, false);

    sprite = sf::Sprite(texture);
    textureSize = sprite.getTextureRect();
}





SlotPos::SlotPos(IsoPos *_isopos)
{
    isopos = _isopos;

    setupSprite();
}





// (--) TEST
void SlotPos::draw( sf::RenderTarget& rt)
{
    WindowSingleton *win;
    win = win->getInstance();


    int y = cpos->y;
    int x = cpos->x;

    // Viewing offset
    y += win->hview->getTopLeft_y();
    x += win->hview->getTopLeft_x();

    sf::Vector2f vpos = {(float)x,(float)y};

    sprite.setPosition(vpos);

    rt.draw(sprite);
}







void SlotPos::dump(std::string ind)
{
    cpos->dump(ind);
    isopos->dump(ind);
}
