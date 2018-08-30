#include "OrMatrix.hpp"
#include "Utilities/Utils.hpp"

OrMatrix::OrMatrix()
{
    std::cout << "Warning: unallocated OrMatrix!\n";
}

OrMatrix::OrMatrix(int _rows,int _cols)
{
    rows = _rows;
    cols = _cols;
    matrix = allocateMatrix(rows,cols);
    allocated = true;
    cpos = new CanvasPos( ORMATRIX_TILE_HEIGHT_PX * rows + 2 , ORMATRIX_TILE_WIDTH_PX * cols + 2);
}

bool OrMatrix::isAllocated()
{
    return allocated;
}



void OrMatrix::setPosition(CanvasPos *cpos)
{

}

void OrMatrix::drawAll(sf::RenderTarget& rt)
{
    if(!allocated) { return ; }

    // TopLeft is the topleft of the internal cpos member

    sf::Vector2f topLeftPos(cpos->y,cpos->x);





    // What are the tile sizes of the orMatrix?
    // Thats a good question...
    // 46 x 46 apparently

    bool everyOtherChangeColor = false;

    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            sf::RectangleShape rect(sf::Vector2f(ORMATRIX_TILE_WIDTH_PX,ORMATRIX_TILE_HEIGHT_PX));  // 46 x 46 px
            rect.setPosition(
                    sf::Vector2f(
                            topLeftPos.x + ( x * ORMATRIX_TILE_WIDTH_PX ),
                            topLeftPos.y + ( y * ORMATRIX_TILE_HEIGHT_PX ) ));   // Figure out where to place them

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

}








