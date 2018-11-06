#include "IsoRect.hpp"

#include "HView.hpp"
#include "Grid.hpp"

#include "Utilities/Utils.hpp"

// 2018-07-22:  Starting to become better but needs more testing... This class is used <everywhere> so regression tests would be nice.


/// \brief Creates an empty rectangle with invalid values
// (--)
IsoRect::IsoRect()
{
    absStart = new IsoPos(-1,-1);
    absEnd = new IsoPos(-1,-1);
    rows = -1;
    cols = -1;
    heightPx = -1;
    widthPx = -1;


	if(drawable) {
        texture.loadFromFile(getFullUri("data\\textures\\GRID2.png"));
        sprite = sf::Sprite(texture);
	}


	//calculateBounds();  dont run this on a dummy object.



}


/// \brief Creates a rectangle given starting positions as integers
// (--)
IsoRect::IsoRect(int _absStartY,
		int _absStartX,
		int _rows,
		int _cols,
		int _heightPx,
		int _widthPx)
{


    rows = _rows;
	cols = _cols;



    // Start position absStart = top left corner of the rect
	absStart = new IsoPos(_absStartY, _absStartX);
	relStart = new IsoPos(0,0);                              // the relative starts at 0,0  aaaaaalways


	// End position absEnd = bottom right corner
	absEnd = new IsoPos(_absStartY + _rows -1 , _absStartX + _cols -1);



	// FIXME Maybe not use these at all, just run calcbounds:
	heightPx = _heightPx;   // Pixel height of texture (w/ mask)
	widthPx = _widthPx;     // Pixel width of texture (w/ mask)



	if(drawable) {
        texture.loadFromFile(getFullUri("data\\textures\\GRID2.png"));
        sprite = sf::Sprite(texture);
	}


	calculateBounds();
}





/// \brief Creates a rectangle given an HPos starting position
// (--)
IsoRect::IsoRect(IsoPos *_absStartPos,
        int _rows,
        int _cols,
        int _heightPx,
        int _widthPx)
{


    rows = _rows;
    cols = _cols;

    // Start position absStart = top left corner of the rect
    absStart = _absStartPos;

	// End position absEnd = bottom right corner
	absEnd = new IsoPos(_absStartPos->y + _rows -1, _absStartPos->x + _cols -1);



    heightPx = _heightPx;       // FIXME Maybe not use these at all, just run calcbounds
    widthPx = _widthPx;


	if(drawable) {
        texture.loadFromFile(getFullUri("data\\textures\\GRID2.png"));
        sprite = sf::Sprite(texture);
	}


    calculateBounds();
}



/// \brief Creates a rectangle given two positions, calculates rows and cols automatically
// (--)
IsoRect::IsoRect(IsoPos *_absStartPos, IsoPos *_absEndPos)
{
    absStart = _absStartPos;
    absEnd   = _absEndPos;
    rows = _absEndPos->y - absStart->y + 1;         // Why +1? because nr of rows starts counting at 1 , not 0 like indexing is, so we have to offset the nr by 1
    cols = _absEndPos->x - absStart->x + 1 ;

    heightPx = -1;
    widthPx = -1;        // FIXME should these be deleted?

	if(drawable) {
        texture.loadFromFile(getFullUri("data\\textures\\GRID2.png"));
        sprite = sf::Sprite(texture);
	}


    calculateBounds();
}





// (++)
int IsoRect::nrTiles()
{
    return rows * cols;
}


/// \brief Checks if searchpos is within the rectangle. Assumes that absEnd is set!
// (--)
bool IsoRect::containsIsoPos(IsoPos *searchPos)
{
    if(searchPos->y >= absStart->y
       &&
       searchPos->y <= absEnd->y
       &&
       searchPos->x >= absStart->x
       &&
       searchPos->x <= absEnd->x) {

           return true;
       }

       return false;
}



// (--)
void IsoRect::calculateBounds()
{

    // We have starting isopos
    // We have rows and cols

    CanvasPos *topBound = new CanvasPos(-1,-1);
    CanvasPos *rightBound = new CanvasPos(-1,-1);
    CanvasPos *bottomBound = new CanvasPos(-1,-1);
    CanvasPos *leftBound = new CanvasPos(-1,-1);



    // Setup extreme limits
    int minX = 9990;
    int minY = 9990;
    int maxX = 0;
    int maxY = 0;

    int x;


    /// Go over every tile

    // Look for min and max positions
    // Update Bound positions as the min max are found



    for(int Y= absStart->y; Y <= (absStart->y + rows -1) ; Y++){            // Why -1? Because "rows" dont start counting at 0, they start at 1. So offset indexing by -1 to get the right value.

        for(int X= absStart->x; X <= (absStart->x + cols -1); X++) {


            // FIXME untested:
            logErr("functions missing\n");

            // CanvasPos *cpos = Grid::convert_iso_to_gpix_topleft(new IsoPos(Y,X), 1);

            /*
            x = Grid::convert_iso_to_gpix_x_topleft(Y,X, GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT, 1);
            y = Grid::convert_iso_to_gpix_y_topleft(Y,X, GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT, 1);



            if(x < minX) {
                minX = x;
                leftBound->y = Y;
                leftBound->x = X;
                leftBound->x = cpos->x;
                leftBound->y = cpos->y;
            }

            if(x > maxX) {
                maxX = cpos->x;
                rightBound->y = Y;
                rightBound->x = X;
                rightBound->x = cpos->x + GRID_TEXTURE_WIDTH;
                rightBound->y = cpos->y;
            }

            if(cpos->y < minY) {
                minY = cpos->y;
                topBound->y = Y;
                topBound->x = X;
                topBound->y = cpos->y;
                topBound->x = cpos->x;
            }

            if(cpos->y > maxY) {
                maxY = cpos->y;
                bottomBound->y = Y;
                bottomBound->x = X;
                bottomBound->y = cpos->y + GRID_TEXTURE_HEIGHT;
                bottomBound->x = cpos->x;
            }
            */
        }

    }


    // FIXME delete this? heightpx and widthpx are nonsense that are too ambigious to use
    heightPx = maxY;
    widthPx = maxX;



    topB = topBound;
    rightB = rightBound;
    bottomB = bottomBound;
    leftB = leftBound;

}




// Please note: +-1 error possible, should it go to <= or to < when matching bounds? should we have a function insideXPixlesOrOnBounds which uses >= and <= ?
// (--) Test, very buggy
bool IsoRect::insideXPixles_middle(CanvasPos *pxPos)
{
    int debugLevel = 0;

    int thisLeft = this->leftB->x;
    int thisRight = this->rightB->x;

    int searchX = pxPos->xmid;

    if(debugLevel >= 1)
    {
        std::cout << "IsoRect.leftBound = " << thisLeft << "    vs   pxPos.x= " << searchX <<  " vs  IsoRect.rightBound= " << thisRight << "\n";
    }

    if(thisLeft <= searchX && searchX < thisRight) {
        return true;
    }



    return false;
}




// (--) test
bool IsoRect::insideYPixles_middle(CanvasPos *pxPos)
{
    int debugLevel = 0;

    int thisTop   = this->topB->y;
    int thisBottom = this->bottomB->y;

    int searchY = pxPos->ymid;


     if(debugLevel >= 1)
    {
        std::cout << "IsoRect.topBound = " << thisTop << "    vs   pxPos.y= " << searchY <<  " vs  IsoRect.bottomBound= " << thisBottom << "\n";
    }


    if(thisTop <= searchY && searchY < thisBottom) {
        return true;
    }



    return false;
}





// (--) test
IsoRect *IsoRect::clone()
{
    std::cout << "Needs BOUND cloning too!\n";
    IsoRect *other = new IsoRect(this->absStart->clone(), this->rows, this->cols, this->heightPx, this->widthPx);

    other->relStart = this->relStart->clone();

    return other;
}




// (--)
void IsoRect::dump(std::string ind)
{
     std::cout << ind << "IsoRect " << absStart->absToString() << " to (" << absStart->y + (rows-1)<< ", " << absStart->x + (cols-1)<< ")\n";
}




// (--)
void IsoRect::fullDump(std::string ind)
{

// Full Dump:
    std::cout << ind << "absStart->y = " << absStart->y << "\n";
    std::cout << ind << "absStart->x = " << absStart->x << "\n";
    std::cout << ind << "rows = " << rows << "\n";
    std::cout << ind << "cols = " << cols << "\n";
    std::cout << ind << "absStart->y + (rows-1)= " << absStart->y + (rows-1) << "\n";
    std::cout << ind << "absStart->x + (cols-1) = " << absStart->x + (cols-1) << "\n";

}





// Regression test
// (-+)
void IsoRect::testFunctions()
{
    std::cout << "\n\n IsoRect - testFunctions()----------------------------\n";
    IsoRect *rect1 = new IsoRect(0,0, 10,10, 32, 64);   // GRID size
    IsoRect *rect2 = new IsoRect(0,0, 10,10, 32, 64);   // GRID size
    IsoRect *rect3 = nullptr;
    IsoRect *rect4a = new IsoRect(new IsoPos(1,0), 10,10, 32, 64);
    IsoRect *rect4b = new IsoRect(1,0 , 10,10, 32, 64);

    std::cout << "\n\nRECT1:\n";
    rect1->dump("  ");
    std::cout << "\n\nRECT2:\n";
    rect2->dump("  ");
    rect3 = rect1->clone();
    std::cout << "\n\nRECT3 (clone of rect1):\n";
    rect3->dump("  ");
    std::cout << "\n\nRECT4a:\n";
    rect4a->dump("  ");
    std::cout << "\n\nRECT4b:\n";
    rect4b->dump("  ");



    std::cout << "\n\nTesting absToString:\n";
    std::cout << "  " <<  rect1->absToString() << "\n";
    std::cout << "  " << rect2->absToString() << "\n";
    std::cout << "  " << rect3->absToString() << "\n";
    std::cout << "  " << rect4a->absToString() << "\n";
    std::cout << "  " << rect4b->absToString() << "\n";




    // Should not fail
    assert(rect1->compare(rect2) == 0);
    assert(rect1->compare(rect3) == 0);
    assert(rect2->compare(rect1) == 0);
    assert(rect2->compare(rect3) == 0);

    assert(rect4a->compareAbsStartPoint(rect4b) == 0);










    std::cout << "\n IsoRect Tests complete -------------------------\n\n";

}


// (--) // FIXME remove the heightpx and widthpx
int IsoRect::compare(IsoRect *other)
{

    // Compare positions
    if(other->absStart->compare(this->absStart) == 0) {

        if(other->rows == this->rows &&
           other->cols == this->cols &&
           other->heightPx == this->heightPx &&
           other->widthPx == this->widthPx) {

               if(other->relStart->compare(this->relStart) == 0) {
                    return 0;
               }
           }
    }

    return -1;

}



// (--) test
int IsoRect::compareAbsStartPoint(IsoRect *other)
{
    if(other->absStart->compare(this->absStart) == 0) {
        return 0;
    }

    return -1;


}


// (--) test
int IsoRect::compareSize(IsoRect *other)
{
    if(this->rows == other->rows
       &&
       this->cols == other->cols) {
           return 0;
       }

    return -1;
}





std::string IsoRect::relToString()
{
    return relStart->relToString();
}



std::string IsoRect::absToString()
{
    std::string str = "IsoRect ";
    str += absStart->absToString();
    str += " to (";
    str += std::to_string(absStart->y + (rows-1));
    str += ", " ;
    str += std::to_string(absStart->x + (cols-1));
    str += ")";
    return str;
}




// (--)
void IsoRect::draw(sf::RenderTarget& rt)
{

    WindowSingleton *win;
    win = win->getInstance();
    HView *hview = win->hview;

    if(drawable) {

        // Create Grid objects and draw them as you would the grid, but with different texture

        for(int Y=this->absStart->y; Y < (this->absStart->y + this->rows); Y++) {

            for(int X=this->absStart->x; X < (this->absStart->x + this->cols); X++) {
                /*
                sf::Vector2f vecpos = sf::Vector2f();

                CanvasPos *cpos = Grid::convert_iso_to_gpix_topleft(new IsoPos(Y,X), 0);
                currPos.y = Grid::convert_iso_to_gpix_y_topleft(Y,X, GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT, 0);
                currPos.x = Grid::convert_iso_to_gpix_x_topleft(Y,X, GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT, 0);

                vecpos.y += hview->getTopLeft_y();
                vecpos.x += hview->getTopLeft_x();

                sprite.setPosition(vecpos);
                rt.draw(sprite);

                */

            }
        }


    }
}









	/*

/// @param _y Vertical positioning, or on the isometric board= M the sloping down and left.
/// @param _x Horizontal positioning, or on the isometric board= N the sloping down and right
/// @param positionType USE_ISO or USE_GPIX , choose what values to store away.
/// (++)
HPos::HPos(int _y, int _x, int positionType)
{
    if(positionType == USE_ISO) {
        y = _y;
        x = _x;
        rel_iso_y = _y;
        rel_iso_x = _x;
        gpix_y = 0;
        gpix_x = 0;
    }

    if(positionType == USE_GPIX) {
        y = 0;
        x = 0;
        rel_iso_y = 0;
        rel_iso_x = 0;
        gpix_y = _y;
        gpix_x = _x;

    }
}


// (++)
HPos::HPos()
{
    y = 0;
    x = 0;
    rel_iso_y = 0;
    rel_iso_x = 0;
    gpix_y = 0;
    gpix_y = 0;
}



// (+-)
std::string HPos::absToString()
{
    std::string str = "(";

    str += std::to_string(y);

    str += "," ;

    str += std::to_string(x);

    str += ")";

    return str;
}





// (-+)
std::string HPos::relToString()
{
    std::string str = "(";

    str += std::to_string(rel_iso_y);

    str += "," ;

    str += std::to_string(rel_iso_x);

    str += ")";

    return str;
}



/// \brief If "other" is an exact match to "this", we return 0.
/// \return 0 on exact match, -1 if not.
// (--) TEST
int HPos::compare(HPos *other)
{

    if(other->y == this->y
       &&
       other->x == this->x
       &&
       other->gpix_y == this->gpix_y
       &&
       other->gpix_x == this->gpix_x
       &&
       other->rel_iso_y == this->rel_iso_y
       &&
       other->rel_iso_x == this->rel_iso_x
    )
    {
        return 0;
    }

    return -1;
}



/// \brief If "Other" has exact match with "this" on absolute_iso positioning, return 0.
/// \return 0 on match, -1 if not.
// (--)
int HPos::compareAbsIso(HPos *other)
{

    if(other->y == this->y
       &&
       other->x == this->x)
    {
        return 0;
    }

    return -1;

}




// Used by roadnetwork.cpp in createSlotPathFromDijkstraResult
// Makes a slotpos appear in the middle of an isometric tile/block
// (-+)
void HPos::transform_gpix_to_slotpos(SlotPos *slotpos, HPos *hpos)
{
    slotpos->hpos->gpix_y += 12;
    slotpos->hpos->gpix_x += 10;
}




/// @brief Copies all the values from the original to the new one, returns newly allocated HPos
// (-+) Seems to work.. // 2018-05-10
HPos *HPos::clone()
{
    HPos *_pos = new HPos(y, x, USE_ISO);
    _pos->rel_iso_y = rel_iso_y;
    _pos->rel_iso_x = rel_iso_x;
    _pos->gpix_y = gpix_y;
    _pos->gpix_x = gpix_x;

    return _pos;
}



// (++)
void HPos::dump(std::string ind)
{
    std::cout << ind << "{\n";
    std::cout << ind << "  abs_iso   y=" << y << ", x=" << x << "\n";
    std::cout << ind << "  rel_iso   y=" << rel_iso_y << ", x=" << rel_iso_x << "\n";
    std::cout << ind << "  gpix      y=" << gpix_y << ", x=" << gpix_x << "\n";
    std::cout << ind << "}\n";
}







/// TEST FUNCTIONS


// private function
void HPos::testFunctions()
{


    HPos *A = new HPos(0,0,USE_ISO);
    HPos *B = new HPos(0,1,USE_ISO);
    HPos *C = new HPos(2,2,USE_ISO);

    HPos *D = new HPos(320,240,USE_GPIX);
    HPos *E = new HPos(480,240,USE_GPIX);
    HPos *F = new HPos(240,480,USE_GPIX);


    HPos *AA = new HPos(0,0,USE_ISO);
    HPos *BB = new HPos(0,1,USE_ISO);
    HPos *CC = new HPos(2,2,USE_ISO);

    HPos *DD = new HPos(320,240,USE_GPIX);
    HPos *EE = new HPos(480,240,USE_GPIX);
    HPos *FF = new HPos(240,480,USE_GPIX);




    // Comparing ISO values
    assert(HPos::compareTwoAbsIso(A,AA) == 0);
    assert(HPos::compareTwoAbsIso(B,BB) == 0);
    assert(HPos::compareTwoAbsIso(C,CC) == 0);



    // Comparing GPIX values
    assert(HPos::compareTwoGpix(D,DD) == 0);
    assert(HPos::compareTwoGpix(E,EE) == 0);
    assert(HPos::compareTwoGpix(F,FF) == 0);


    std::cout << "These SHOULD fail: \n";

    //assert(HPos::compareTwoAbsIso(A,BB) == 0);
    //assert(HPos::compareTwoAbsIso(B,AA) == 0);
    //assert(HPos::compareTwoAbsIso(C,AA) == 0);

    //assert(HPos::compareTwoGpix(D,EE) == 0);
    //assert(HPos::compareTwoGpix(E,FF) == 0);
    //assert(HPos::compareTwoGpix(F,EE) == 0);




}
*/

