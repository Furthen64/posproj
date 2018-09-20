#include "IsoMatrix.hpp"
#include "Utilities/Utils.hpp"
#include "Singletons/ResourceHolder.hpp"

IsoMatrix::IsoMatrix()
{
    std::cout << "Warning: unallocated IsoMatrix!\n";

    {
        ResourceHolder *resHolder;
        resHolder = resHolder->getInstance();

        int _textureId = 551;
        std::string textureName = resHolder->getTextureNameByIndex(_textureId);

        bool result = resHolder->applyTexture(textureName, &texture, true);

        if(!result) {
            std::cout << "ERROR GameMatrix creation, cannot find texture id \"" << _textureId << "\".\n";
            return ;
        }
    }

    sprite = sf::Sprite(texture);
}


/// \brief Creates a dummy isomatrix with no real data
IsoMatrix::IsoMatrix(int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;

    orMat = new OrMatrix(_rows, _cols);
}



/// Problems we have to think about
/// Changing one part of this matrix, needs to run an updatefunction that updates the topleft and updates the lrect and its bounding box. Yes? pLease?
IsoMatrix::IsoMatrix(OrMatrix *_orMat)
{
    if(_orMat == nullptr) {
        logErr(cn + " constructor failed, nullptr argument\n");
        throw std::runtime_error( "ERROR:  constructor IsoMatrix failed, nullptr argument" );
    }

    orMat = _orMat;

    topleft = orMat->getTopLeft_cpos()->clone();

    lrect = new LineRect( new CanvasPos(topleft->y, topleft->x),
                          new CanvasPos(topleft->y, topleft->x + (orMat->getCols() * ORMATRIX_TILE_WIDTH_PX) ),
                          new CanvasPos(topleft->y+(orMat->getRows() * ORMATRIX_TILE_HEIGHT_PX), topleft->x+ (orMat->getCols() * ORMATRIX_TILE_WIDTH_PX) ),
                          new CanvasPos(topleft->y+(orMat->getRows() * ORMATRIX_TILE_HEIGHT_PX), topleft->x) );


    setTopLeft(topleft); // Run this to update lrect's topleft


    /*

    Use these to try out specific shapes:

    std::cout << "Remember: IsoMatrix is set to HARDCODED values!\n\n";
    lrect = new LineRect(new CanvasPos(46,92),
                         new CanvasPos(92,138),
                         new CanvasPos(138,92),
                         new CanvasPos(92,46)); // 45 deg rotated square

    lrect = new LineRect( new CanvasPos(0,46),
                          new CanvasPos(138,92),
                          new CanvasPos(276,46),
                          new CanvasPos(138,0) ); // Squashed square

    lrect = new LineRect(new CanvasPos(46,92),
                         new CanvasPos(92,138),
                         new CanvasPos(368,92),
                         new CanvasPos(92,46));*/


}





int IsoMatrix::getCols()
{
    return cols;
}

int IsoMatrix::getRows()
{
    return rows;
}


OrMatrix *IsoMatrix::getOrMatrix()
{
    return orMat;
}


void IsoMatrix::setTopLeft(int _y, int _x)
{
    setTopLeft(new CanvasPos(_y, _x));
}

// (-+)
void IsoMatrix::setTopLeft(CanvasPos *_topleft)
{
    // Update our topleft and also our LRect object so all the A,B,C,D's are updated
    topleft = _topleft;
    lrect->setTopLeft(_topleft);
}



/// Beware: works with limited amount of shapes!
void IsoMatrix::setPosByNewMiddle(CanvasPos *_cpos)
{
    lrect->moveByMiddle(_cpos);
}


void IsoMatrix::moveToOrigo()
{
    // Store away old position of middle
    prev_cpos = getMiddle_cpos()->clone();
    setPosByNewMiddle(new CanvasPos(0,0));  // Move the object (by middle) to origo
}


void IsoMatrix::moveBack()
{
    // Return the object to its previous position, by middle , not topleft
    setPosByNewMiddle(prev_cpos);
}

CanvasPos *IsoMatrix::getMiddle_cpos()
{
    return lrect->getMiddle_cpos();
}

CanvasPos *IsoMatrix::getTopLeft_cpos()
{
    return topleft;
}

void IsoMatrix::scale_y(float scaleFactor)
{
    moveByTopLeftSaveMiddle(new CanvasPos(0,0));
    lrect->scale_y( scaleFactor );
    moveBack();
}





void IsoMatrix::rotateNDegCCW(float n)
{

    moveToOrigo();
    {
        // Move to origo and back? for now does it where it is, against a origo in cpos(0,0)
        lrect->rotateAllPointsNDegCCW(n);
        topleft = lrect->getTopLeft()->clone();
    }
    moveBack();
}

void IsoMatrix::rotateNDegCW(float n)
{

    // Move to origo and back? for now does it where it is, against a origo in cpos(0,0)
    moveToOrigo();
    {
        lrect->rotateAllPointsNDegCW(n);
        topleft = lrect->getTopLeft()->clone();
    }
    moveBack();
}


void IsoMatrix::drawAll(sf::RenderTarget& rt)
{

    lrect->drawAll(rt);

    /*
    sf::Vector2f topLeftVec(topleft->y,topleft->x);

    // What are the tile sizes of the IsoMatrix?
    // Thats a good question...
    // 46 x 46 apparently

sf::RectangleShape spinRect(sf::Vector2f(460,460));
spinRect.setRotation(45);
spinRect.setFillColor(sf::Color(125,125,100,255));
spinRect.setOutlineColor(sf::Color(255,255,255,255));
spinRect.setOutlineThickness(1.0f);


rt.draw(spinRect);
*/
/*
    bool everyOtherChangeColor = false;
    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            sf::RectangleShape rect(sf::Vector2f(IsoMatrix_TILE_WIDTH_PX,IsoMatrix_TILE_HEIGHT_PX));  // 46 x 46 px
            rect.setPosition(
                    sf::Vector2f(
                            topLeftVec.x + ( x * IsoMatrix_TILE_WIDTH_PX ),
                            topLeftVec.y + ( y * IsoMatrix_TILE_HEIGHT_PX ) ));   // Figure out where to place them

            if(everyOtherChangeColor) {
                rect.setFillColor(sf::Color(209,175,21,125));   // Lovely orange
                everyOtherChangeColor = !everyOtherChangeColor;
            } else {
                rect.setFillColor(sf::Color(203,77,43,125));   // Reddish
                everyOtherChangeColor = !everyOtherChangeColor;
            }
            rt.draw(rect);
        }
        everyOtherChangeColor = !everyOtherChangeColor;
    }
    */

}







// (-+)
void IsoMatrix::moveByTopLeftSaveMiddle(CanvasPos *_cpos)
{

    prev_cpos = getMiddle_cpos();

    setTopLeft(_cpos);

}
