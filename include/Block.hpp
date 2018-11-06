#ifndef BLOCK_H
#define BLOCK_H



#include <SFML/Graphics.hpp>

#include "../src/Singletons/ResourceHolder.hpp"
#include "Utilities/Utils.hpp"
#include "IsoPos.hpp"
#include "IsoMatrix.hpp"
#include "Constants.hpp"



/// //////////////////////////////////////////////
/// (--) Block
/// ? x ? pixels        Auto adjusted where its positioned for drawing based upon its texture resolution

class Block
{
public:

    Block(IsoPos *, std::string );
    Block(IsoPos *, int );
    Block(CanvasPos *, std::string );

void draw( sf::RenderTarget& rt);

    void dump(std::string);
    void minimaldump(std::string ind);

void setPos(CanvasPos *_cpos);
void setPos(IsoPos  *_isopos);



IsoPos *get_isopos();
CanvasPos *get_cpos();



    int getTextureID();

    void setTextureByName(std::string _textureName);

    Block *clone();

    std::string getTextureName();

    void set_gpix_pos_by_abs_iso(IsoPos *_abs_iso);
    void setCanvasPos_byIsoPos(IsoPos *isopos);




private:
    int textureID;
    sf::Texture texture;
    sf::IntRect textureSize;
    std::string textureName;
    sf::Sprite sprite;
    sf::Vector2f pos_vec2f;

    std::string cn = "Block.cpp";
    IsoPos *isopos;
    CanvasPos *cpos;
};

#endif
