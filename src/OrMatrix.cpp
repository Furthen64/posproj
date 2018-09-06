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
    topleft = new CanvasPos( (ORMATRIX_TILE_HEIGHT_PX * rows) + 2 ,
                          (ORMATRIX_TILE_WIDTH_PX * cols) + 2);
}

bool OrMatrix::isAllocated()
{
    return allocated;
}



// (-+)
void OrMatrix::setPosition(CanvasPos *_topleft)
{
    if(_topleft == nullptr) {
        logErr(cn + " setPosition() got nullptr\n");
    }
    topleft = _topleft;

}

void OrMatrix::drawAll(sf::RenderTarget& rt)
{
    if(!allocated) { return ; }

    sf::Vector2f topLeftVec(topleft->x,topleft->y);

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
                            topLeftVec.x + ( x * ORMATRIX_TILE_WIDTH_PX ),
                            topLeftVec.y + ( y * ORMATRIX_TILE_HEIGHT_PX ) ));   // Figure out where to place them

            if(everyOtherChangeColor) {
                rect.setFillColor(sf::Color(209,175,21,125));   // Lovely orange
                everyOtherChangeColor = !everyOtherChangeColor;
            } else {
                rect.setFillColor(sf::Color(203,77,43,125));   // Reddish
                everyOtherChangeColor = !everyOtherChangeColor;
            }
            rt.draw(rect);
        }
        if(cols%2==0) {
            everyOtherChangeColor = !everyOtherChangeColor;
        }
    }

}


CanvasPos *OrMatrix::getTopLeft_cpos()
{
    return topleft;
}








