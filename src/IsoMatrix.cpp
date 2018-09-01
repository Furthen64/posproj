#include "IsoMatrix.hpp"
#include "Utilities/Utils.hpp"

IsoMatrix::IsoMatrix()
{
    std::cout << "Warning: unallocated IsoMatrix!\n";
}

IsoMatrix::IsoMatrix(OrMatrix *_orMat)
{
    if(_orMat == nullptr) {
        logErr(cn + " constructor failed, nullptr argument\n");
        throw std::runtime_error( "ERROR:  constructor IsoMatrix failed, nullptr argument" );

    }
    orMat = _orMat;
    topleft = new CanvasPos( (ORMATRIX_TILE_HEIGHT_PX * orMat->getRows()) + 2 ,
                             (ORMATRIX_TILE_WIDTH_PX * orMat->getCols()) + 2);
}



// (-+)
void IsoMatrix::setPosition(CanvasPos *_topleft)
{
    if(_topleft == nullptr) {
        logErr(cn + " setPosition() got nullptr\n");
    }
    topleft = _topleft;

}

void IsoMatrix::drawAll(sf::RenderTarget& rt)
{


    sf::Vector2f topLeftVec(topleft->y,topleft->x);

    // What are the tile sizes of the IsoMatrix?
    // Thats a good question...
    // 46 x 46 apparently

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








