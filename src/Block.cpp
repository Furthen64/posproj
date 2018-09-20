#include "Block.hpp"




// A Block is a thing that gets rendered on an isometric tile, like a House, Road or a Tree.
// Its texture resolution determines the correct height for positioning on that tile.
//
// All the Blocks on the gameboard are stored in a "HurkaMap" object, used by Core



/// Block constructor
///
/// @param _hpos         An HPos object with the absolute iso positions set
/// @param texturename   Unique string to identify a texture object with, e.g. "HOUSE001", see TextureManager class
///
/// (-+)
Block::Block(IsoPos *_hpos, std::string _textureName)
{
    int debugLevel = 0;


    if(_textureName == "") {
        std::cout << "ERROR " << cn << " Could not create block with empty texturename=" << _textureName << "\"!\n";
        return ;
    }


    // Apply texture
    ResourceHolder *res;
    res = res->getInstance();


    bool result = res->applyTexture(_textureName, &texture, false);
    if(!result) { std::cout << "ERROR Block creation, cannot find texture \"" << _textureName << "\".\n";  return ;  }

    textureName = _textureName;



    // Set SFML sprite
    sprite = sf::Sprite(texture);
    textureSize = sprite.getTextureRect();


    if(debugLevel > 0) {
        std::cout << "height= " << textureSize.height << ", width=" << textureSize.width << "\n";
    }


    // Now we have texture size, set the gPix positions
    set_gpix_pos_by_abs_iso(_hpos);
}


/// Block constructor, create a block by supplying texture id as an integer
///
/// @param _hpos         An HPos object with the absolute iso positions set
/// @param _textureId    Unique integer to identify a texture object with, e.g. 001 which maps to "HOUSE001", see TextureManager class
// (-+)
Block::Block(IsoPos *_hpos, int _textureId)
{
    int debugLevel = 0;

    ResourceHolder *res;
    res = res->getInstance();


    textureName = res->getTextureNameByIndex(_textureId);

    bool result = res->applyTexture(textureName, &texture, false);

    if(!result) {
        std::cout << "ERROR Block creation, cannot find texture id \"" << _textureId << "\".\n";
        return ;
    }

    sprite = sf::Sprite(texture);

    textureSize = sprite.getTextureRect();


    if(debugLevel > 0) {
        std::cout << "height= " << textureSize.height << ", width=" << textureSize.width << "\n";
    }

    set_gpix_pos_by_abs_iso(_hpos);

}





/// Uses the internal "hpos" object for gameworld position (e.g. it's at iso position {7,1} and at gamepix position {1000,600} )
/// and the "viewpos" viewing position object to know where we are looking at the moment
///
/// @param rt       SFML RenderWindow thingie
/// @param viewPos  A rectangle which holds the starting x and starting y for looking at the gameboard
// (-+)
void Block::draw( sf::RenderTarget& rt)
{
    logErr("block draw stub\n");
    /*
    int x = hpos->x;
    int y = hpos->y;


    // Viewing offset
    x += viewHPos->x;
    y += viewHPos->y;


    sf::Vector2f _pos = {(float)x,(float)y};


    sprite.setPosition(_pos);

    rt.draw(sprite);
    */

}



// (-+)
void Block::setTextureByName(std::string _textureName)
{


    ResourceHolder *res;
    res = res->getInstance();


    textureName = _textureName;


    bool result = res->applyTexture(_textureName, &texture, false);


    if(!result) {
        std::cout << "ERROR " << cn << " setTextureByName(), cannot find texture \"" << _textureName << "\".\n";
        return ;
    }

    sprite = sf::Sprite(texture);

    textureSize = sprite.getTextureRect();

    std::cout << "height= " << textureSize.height << ", width=" << textureSize.width << "\n";


}




// Sets the position by a hpos object,
// The only thing we know is set is the "abs_iso" position data
//
// (--) untested

void Block::setCanvasPos_byIsoPos(IsoPos *isopos)
{
    logErr("setCanvasPos_byIsoPos untested!\n");


}
void Block::set_gpix_pos_by_abs_iso(IsoPos *_abs_iso)
{
    logErr("block set_gpix_pos_by_abs_iso stub!\n");
    /*
    hpos = _abs_iso;

    hpos->gpix_y_middle = Grid::isoToGpixMiddleY(_abs_iso, 2, 0);
    hpos->gpix_x_middle = Grid::isoToGpixMiddleX(_abs_iso, 2, 0 );

    hpos->x = Grid::convert_iso_to_x(hpos->y, hpos->x, textureSize.width, textureSize.height, 2);
    hpos->y = Grid::convert_iso_to_y(hpos->y, hpos->x, textureSize.width, textureSize.height, 2);
*/

}



// (++)
void Block::dump(std::string ind)
{
    logErr("block dump stub\n");
/*    std::cout << "\n\n" << ind << "----------------- block " << hpos->absToString() << " ------------------\n";
    std::cout << ind << "position:\n";
    std::cout << ind << "  absolute iso position = " << hpos->y << ", " << hpos->x << "\n";
    std::cout << ind << "  relative iso position = " << hpos->rely << ", " << hpos->relx << "\n";
    std::cout << ind << "  topleft pixel position = " << hpos->y << ", " << hpos->x << "\n";
    std::cout << ind << "  middle of tile pixel position = " << hpos->gpix_y_middle << ", " << hpos->gpix_x_middle << "\n";
    std::cout << ind << "Texture: " << textureName << "\n";
    std::cout << ind << "ID: " << textureID << "\n";
    std::cout << ind << "texturesize: " << textureSize.height  << " x " << textureSize.width << "\n";
    */
}


// (-+)
void Block::minimaldump(std::string ind)
{
    logErr("block minimaldump stub\n");
    /*
    std::cout << ind << " -- Block (" << textureName << ") -- \n";
    std::cout << ind << "abs position= " << hpos->absToString() << "\n";
    std::cout << ind << "rel position= " << hpos->relToString() << "\n";
    */
}





// (--) TEST
Block *Block::clone()
{
    std::cout << "Block.clone(): UNDEFINED BEHAVIOUR !! Needs more testing.\n";

    Block *block = new Block(hpos->clone(), textureName);

    return block;
}




/// \return The internal Hpos pointer!
// (--)
IsoPos *Block::getHPos()
{
    return hpos;
}





int Block::getTextureID()
{
    return textureID;
}


std::string Block::getTextureName()
{
    return textureName;
}
