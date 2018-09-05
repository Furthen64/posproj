#include "IsoMatrix.hpp"
#include "Utilities/Utils.hpp"

IsoMatrix::IsoMatrix()
{
    std::cout << "Warning: unallocated IsoMatrix!\n";
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
    topleft = new CanvasPos( (ORMATRIX_TILE_HEIGHT_PX * orMat->getRows()) + 2 ,
                             (ORMATRIX_TILE_WIDTH_PX * orMat->getCols()) + 2);


    std::cout << "IsoMatrix topleft_cpos = (" << topleft->y << ", " << topleft->x << ")\n";

    // Exact square copy of the Ortho Matrix
    /*lrect = new LineRect( new CanvasPos(topleft->y, topleft->x),
                          new CanvasPos(topleft->y, topleft->x + 460),
                          new CanvasPos(topleft->y+460, topleft->x+460),
                          new CanvasPos(topleft->y+460, topleft->x) );
                          */



    std::cout << "IsoMatrix constructor hardcoded debug\n\n";
    lrect = new LineRect(new CanvasPos(46,92),
                         new CanvasPos(92,138),
                         new CanvasPos(138,92),
                         new CanvasPos(92,46));
    setTopLeft(new CanvasPos(46,46));

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

void IsoMatrix::setMiddleToCpos(CanvasPos *cpos)
{
    lrect->setTopLeft(new CanvasPos(-46,-46));
    // Find middle point
    std::cout << "find middle point\n";

    // Set all points around it
    std::cout << "setmiddle stub\n";
}




void IsoMatrix::scale2x()
{
    lrect->setSize_y( lrect->getSize_y() * 2.0f);
}


void IsoMatrix::rotateNDegCCW(float n)
{
    // Move to origo and back? for now does it where it is, against a origo in cpos(0,0)
    lrect->rotateAllPointsNDegCCW(n);

    // Update topleft now that we've altered the points



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








