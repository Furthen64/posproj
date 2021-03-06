#include "Grid.hpp"

#include "HView.hpp"

/// Grid contains a lot of static position functions used everywhere
/// also contains draw() function so you can see the iso grid

// (-+)
Grid::Grid(int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;


    texture.loadFromFile(getFullUri("data\\textures\\GRID3.png"));
    sprite = sf::Sprite(texture);

    textureSelected.loadFromFile(getFullUri("data\\textures\\GRID_SELECTED.png"));
    spriteSelected = sf::Sprite(textureSelected);

    // Load font
    if (!font.loadFromFile( getFullUri("data\\fonts\\consola.ttf")))
    {
        std::cout << "ERROR " << cn << " could not load font.\n";
    }
}


// todo needs rework i need to know exactly where and how this scales and positions!!! 2018-11
void Grid::draw( sf::RenderTarget& rt)
{


    //std::cout << "grid.draw()       Grid size:\n";
    //std::cout << "grid.draw()       Bounding box size:\n";

/*
    todo
    this needs a bounding box
    one that automatically generates when we know the grid size!

    and

    also needs x and y offset
*/
    CRect *boundingBox = nullptr;           // Used to move this around and to know the x and y offset to origo
    CanvasPos *topLeft_cpos = nullptr;      // The x and y offset from origo











    // Unsure of this stuff:




    IsoPos *isopos;
    CanvasPos *cpos;
    WindowSingleton *win;
    win = win->getInstance();

    // Draw Y x X amount of grid tiles at the right positions
    for(int Y = 0; Y < rows; Y++) {

        for(int X = 0; X < cols; X++) {

             // Generate IsoPos for each tile
             isopos = new IsoPos(Y,X);

             // Generate correct CanvasPos for each tile and draw it
             cpos = Grid::itoc(isopos);

          //   cpos->dump("grid-cpos: ");

             sprite.setPosition( cpos->getSfVec() );
             rt.draw(sprite);

        }
    }

}



void Grid::setSelectedTile(CanvasPos *_pos)
{
    if(_pos == nullptr) {
        std::cout << "WARNING: setVisible: _pos is nullptr!\n";
        return ;
    }

    drawSelectedTile = true;

    selectedTile_vec2f = _pos->getSfVec();

}



void Grid::hideSelectedTile()
{
    drawSelectedTile = false;
}



/// \brief Converts gpix values to iso position, great for converting mouse click position to an iso tile
/// \param rt can be null
/// \param viewhpos can be null these are only used for painting on canvas if needed for debug reasons
// For now its easy to make it spin out of control, needs more safety features.
// (--)
/*

IsoPos *Grid::findTile(HRect *entireGameBoard, CanvasPos *searchpos_gpix_middle, std::string ind, sf::RenderTarget& rt, std::string recursionName)
{
    int debugLevel = 0;

    if(entireGameBoard->getSize_y() > GAMEMATRIX_MAX_ROWS ||
       entireGameBoard->getSize_x() > GAMEMATRIX_MAX_COLS) {

       std::cout << "ERROR! " << cn << " findTile got an entireGameBoard with a too large hrect.\n";
       return nullptr;
    }


    logErr("grid findtile make adjustment and turn it into a tradition\n");

    return nullptr;

    HRect *relRect = new HRect(
                                    entireGameBoard->absStart,
                                    entireGameBoard->rows,
                                    entireGameBoard->cols,
                                    entireGameBoard->heightPx,
                                    entireGameBoard->widthPx);

    if(debugLevel >=1) {
        std::cout << ind << "\n";
        std::cout << ind << "findTile()-----------------------------\n";
        std::cout << ind << " - entireGameBoard->rect = " << entireGameBoard->absToString() << "\n";
        std::cout << ind << " - relRect = " << relRect->absToString() << "\n";
    }

    if(searchpos_gpix_middle == nullptr) {
        std::cout << "ERROR " << cn << " searchpos is nullptr\n";
        return nullptr;
    }
    if(debugLevel >=1) {std::cout << ind << " - searchpos_gpix_middle= " << searchpos_gpix_middle->gpix_y_middle << "," << searchpos_gpix_middle->gpix_x_middle<< "\n";}


    return findTile(entireGameBoard, relRect, searchpos_gpix_middle, ind, 0, rt, viewHPos, recursionName, debugLevel);

}
          */









/*
// This code no longer needed



/// \brief Given a searchpos with gpix values set, find an iso inside a hmatrix
/// \param entireGameBoard
/// \param relRect A smaller than entireGameBoard rectangle, used in a divide n conquer manner
/// \param searchpos_gpix_middle Gpix values of search position
// RECURSIVE
// (--) Needs more testing, especially after all those changes to gpix position (added topleft and middle)

IsoPos *Grid::findTile(HRect *entireGameboard,
                     HRect *relRect,
                     CanvasPos *searchpos_gpix_middle,
                     std::string ind,
                     int counter,
                     sf::RenderTarget& rt,
                     std::string recursionName,
                     int debugLevel)
{


    for(int n = 0; n < counter; n++) {
        ind += " ";
    }

    /// Error Checking
    {

        if(counter > 20) {
            std::cout << ind << "WARNING: findTile reached limit, counter= " << counter << "\n";
            std::cout << ind << "Too big of a map? Code needs adjusting? Report to Devteam!\n";
            return nullptr;
        }

        if(entireGameboard == nullptr) {
            std::cout << "ERROR " << cn << " findTile() entireGameBoard is nullptr\n";
            return nullptr;
        }


        if(relRect == nullptr) {
            std::cout << "ERROR " << cn << " findTile() relRect is nullptr\n";
            return nullptr;
        }

        if(searchpos_gpix_middle == nullptr) {
            std::cout << "ERROR " << cn << " findTile() searchPos is nullptr\n";
            return nullptr;
        }
    }



    IsoPos *retpos = nullptr;


	if(debugLevel >=1) {
        std::cout << "\n\n";
        std::cout << ind << recursionName << " findTile()---------------------------\n";
        std::cout << ind <<  " current RECT:\n";
        relRect->dump();
	}



	// Make a rough check if we're inside x and y bounds

    if(debugLevel>=1) {std::cout << ind <<  "- insideXpixels: ";}
    if( !relRect->insideXPixles_middle( searchpos_gpix_middle ) ) {
        if(debugLevel>=1) {std::cout << ind << " No.\n";}
        return nullptr;
    }
    if(debugLevel>=1) { std::cout << ind << " Yes.\n"; }


    if(debugLevel>=1) {std::cout << ind <<  "- insideYpixels: "; }
    if ( !relRect->insideYPixles_middle( searchpos_gpix_middle ) ) {
        if(debugLevel>=1) {std::cout << ind <<  " No.\n";}
        return nullptr;
    }
    if(debugLevel>=1) {std::cout << ind << " Yes.\n";}




    /// OK - it CAN be inside here, lets check if we need to do bruteforce or just "divide n conquer" again


	int nrTiles = relRect->nrTiles();
	if(debugLevel >=1) { std::cout << ind << "- nrTiles: " << nrTiles << "\n";	}

	if(nrTiles <= 16) {
		return bruteForceFindTile( entireGameboard, relRect, searchpos_gpix_middle, ind, rt, recursionName , debugLevel);                // RECURSION END
	}





	/// Approach it the smart way

	// Divide the submatrix into four squares

    int rows = relRect->getSize_y();
    int cols = relRect->getSize_x();

    int halfRows1 = -1;
    int halfRows2 = -1;
    int halfCols1 = -1;
    int halfCols2 = -1;



    // figure out how to divide the four squares, if rows n cols are not evenly divided by 2


    if(rows%2==0) {
        halfRows1 = rows/2;
        halfRows2 = halfRows1;
    } else {
        halfRows1 = (rows-1)/2;
        halfRows2 = rows - halfRows1  ;
    }


     if(cols%2==0) {
        halfCols1 = cols/2;
        halfCols2 = halfCols1;
    } else {
        halfCols1 = (cols-1)/2;
        halfCols2 = rows - halfCols1    ;
    }


	HRect *sq0, *sq1, *sq2, *sq3;


	/// sq0

	int fromY= relRect->absStart->y;
	int fromX = relRect->absStart->x;
	int toY = fromY + (halfRows1-1);            // halfRows1 is "nr of rows", not index of, so we -1 to get the right value
	int toX = fromX + (halfCols1-1);            // halfcols1 is "nr of cols", not index of, so we -1 to get the right value

	sq0 = new HRect( new HPos(fromY, fromX,   USE_ISO),
	                 new HPos(toY, toX,       USE_ISO));



	/// sq1


	fromY = fromY;         // Keep it as is
	fromX = toX +1;        // Continue from previous square, but add 1 so we dont overlap and run same tiles again
	toY = toY;             // Keep it as is
    toX = toX + halfCols2;

    sq1 = new HRect( new HPos(fromY, fromX,  USE_ISO),
	                 new HPos(toY, toX,      USE_ISO));



    /// sq2

	// Beginning on a new line


	fromY = fromY + halfRows1;          // Start from the offset of sq0 (fromY) and add halfRows1 to get to the right index
	fromX = relRect->absStart->x;
	toY = toY + halfRows2;                      // Add the other half (already redacted -1 in sq0)             //WISHLIST alpha-0.2: omg, this is getting outta hand with these wonky variables... cleanup? rename? new vars?
	toX = fromX + (halfCols1-1);                        // halfcols1 is "nr of cols", not index of, so we -1 to get the right value


    sq2 = new HRect( new HPos(fromY, fromX,  USE_ISO),
	                 new HPos(toY, toX,     USE_ISO));



    /// sq3

	fromY = fromY;                   // Keep as it is
	fromX = fromX + halfCols1;       // Dont redact from halfCols1 this time because we are starting +1 compared to sq2
    toY = toY;                      // Keep as it is
    toX = toX + halfCols2;          // Add the other half (already redacted -1 in sq2)


    sq3 = new HRect( new HPos(fromY, fromX,  USE_ISO),
	                 new HPos(toY, toX,     USE_ISO));


	if(debugLevel >=1) {
        std::cout << "\n";
        std::cout << ind << "We divide up current relrect to these new 4 squares:\n";
        sq0->dump(ind + " sq0: ");
        sq1->dump(ind + "      sq1: ");
        sq2->dump(ind + " sq2: ");
        sq3->dump(ind + "      sq3: ");
	}



	/// Enter each square and look for the grid

	if(debugLevel >=2) {std::cout << ind << " entering sq0: \n"; }
	retpos = findTile(entireGameboard, sq0, searchpos_gpix_middle, ind ,++counter , rt, viewHPos, recursionName + "-sq0", debugLevel);
	if(retpos != nullptr) { return retpos; }

    if(debugLevel >=2) {std::cout << ind << " entering sq1: \n"; }
    retpos = findTile(entireGameboard, sq1, searchpos_gpix_middle, ind, ++counter, rt , viewHPos, recursionName + "-sq1", debugLevel);
    if(retpos != nullptr) { return retpos; }


    if(debugLevel >=2) {std::cout << ind << " entering sq2: \n"; }
    retpos = findTile(entireGameboard, sq2, searchpos_gpix_middle, ind ,++counter , rt, viewHPos, recursionName + "-sq2", debugLevel);
    if(retpos != nullptr) { return retpos; }

    if(debugLevel >=2) {std::cout << ind << " entering sq3: \n"; }
    retpos = findTile(entireGameboard, sq3, searchpos_gpix_middle, ind  ,++counter, rt, viewHPos , recursionName + "-sq3", debugLevel);
    if(retpos != nullptr) { return retpos; }



    return retpos;

}
*/






// Code no longer needed

/*


/// \brief internal function used by "findTile()" to go pixelline by line for every tile inside a relative rect
/// \param entireGameBoard
/// \param relRect A smaller than entireGameBoard rectangle, used in a divide n conquer manner
/// \param searchpos_gpix_middle Gpix values of search position
// (-+) Works, but could use more testing (2018-06)

HPos *Grid::bruteForceFindTile(HRect *entireGameboard, HRect *relRect, HPos *searchpos_gpix_middle, std::string ind, RenderTarget &rt, HPos *viewHPos, std::string recursionName, int debugLevel)
{



    bool debugDrawing  = false; // RenderTarget &rt has to be a normal game/editor window. Not something else....

    if(debugLevel >=1) {
        std::cout << "\n\n\n";
        std::cout << ind <<  "bruteForceFindTile()------------\n";
    }


    HPos *isopos = nullptr;


    // Generate iso pos for all the tiles inside the relrect
    // and check if we're inside it

    // Make sure you use ABSOLUTE positioning, considering the gpix
    // of the searchpos is ABSOLUTE positioned....

    // So DONT set Y=0 and X=0 and go from there
    // You have to figure out the starting position and use the ROWS and COLS
    // of the RELRECT

    int searchPos_gpix_y = searchpos_gpix_middle->gpix_y_middle;
    int searchPos_gpix_x = searchpos_gpix_middle->gpix_x_middle;

    int currentY = -1;

    for(int Y = relRect->absStart->y; Y < (relRect->absStart->y+relRect->rows); Y++)
    {

        for(int X = relRect->absStart->x; X < (relRect->absStart->x+relRect->cols); X++)
        {


            // Current Tile:
            isopos    = new HPos(Y,X,USE_ISO);
            if(debugLevel >=1) {std::cout << ind << " - Current Tile: " << isopos->absToString() << "\n";}

            // Figure out which Y pixelline we're at

            currentY = Grid::convert_iso_to_y(isopos->y, isopos->x, GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT, 0);



            // Draw a White rectangle around the square that is our current tile

            if(debugLevel >=1 && debugDrawing)
            {

                sf::RectangleShape currIsoPosRect(sf::Vector2f(GRID_TEXTURE_WIDTH, GRID_TEXTURE_HEIGHT));
                currIsoPosRect.setPosition(sf::Vector2f( isopos->x + viewHPos->x, isopos->y + viewHPos->y));
                currIsoPosRect.setOutlineThickness(1.0f);
                currIsoPosRect.setOutlineColor(sf::Color(255,255,255));
                currIsoPosRect.setFillColor(sf::Color(0,0,0));

                rt.draw(currIsoPosRect);
            }

            // Rough check if inside x pixel bounds
            // Is this the the way to do it? Shouldnt it check against the hrect bounds? isopos is not a rect, so it does not have those. It has gpixx and we know the grid texture width

            if( isopos->x <= searchPos_gpix_x && searchPos_gpix_x < (isopos->x + GRID_TEXTURE_WIDTH) ) {
                 if(debugLevel >=1) {std::cout << ind << "   - inside x span.\n";}
            } else {
                continue; // No reason to look into pixel by pixel ... Next!
            }


            // Rough check if inside y pixel bounds

            if( isopos->y <= searchPos_gpix_y && searchPos_gpix_y < (isopos->y + GRID_TEXTURE_HEIGHT) ) {
                 if(debugLevel >=1) {std::cout << ind << "   - inside y span.\n";}
            } else {
                continue; // Next!
            }







            ///
            /// Now look at individual pixel lines to see if our gpix y,x is in there
            ///



            //                      ##                  xwidth=2            xoffset=64/2 - width/2
            //                    ##$$##                xwidth=6    (+4)    xoffset=64/2 - width/2
            //                  ##$$##$$##              xwidth=10   (+4)
            //                ##$$##$$##$$##


            // Loop 1 going downwards from a pointy tip


            int xwidth = 2;
            int xoffset = GRID_TEXTURE_WIDTH/2;     // =32 pixels
            xoffset = isopos->x;              // add the position of the Tile we're currently looking at

            int fromX;
            int toX;


            // Debuggies
            int drawFromX;
            int drawFromY;


            fromX = xoffset;
            toX = fromX + xwidth;

            for(int y = 0; y < (GRID_TEXTURE_HEIGHT/2); y++)
            {



                // Draw a red lines along the x-pixels we're looking

                if(debugLevel >=1 && debugDrawing == true)
                {
                    sf::RectangleShape searchLine(sf::Vector2f(xwidth, 1));

                    drawFromX = fromX + viewHPos->x;
                    drawFromY = currentY + viewHPos->y;


                    searchLine.setPosition(sf::Vector2f( drawFromX,
                                                         drawFromY));



                    searchLine.setOutlineThickness(1.0f);
                    searchLine.setOutlineColor(sf::Color(255,0,0));
                    searchLine.setFillColor(sf::Color(255,0,0));

                    rt.draw(searchLine);

                }

                if( fromX <= searchPos_gpix_x && searchPos_gpix_x < toX ) {
                    if(currentY == searchPos_gpix_y) {

                        // inside?
                        if(debugLevel >=1) {std::cout << ind << " - - -  Eureka!  we are inside " << fromX << " - ( " << searchPos_gpix_y << " ) - " << toX << "\n";}
                        return isopos;
                    }
                }

                // No luck, please go down one pixelline and increase Xwidth and adjust fromX
                xwidth+=4;


                // Adjust fromX
                fromX = isopos->x;
                fromX += GRID_TEXTURE_WIDTH/2;
                fromX -= (int)floor(xwidth/2);

                // Adjust toX
                toX = fromX + xwidth;

                // Next line? increment currentY
                currentY++;

            }



            //
            //                ##$$##$$##$$##
            //                  ##$$##$$##
            //                    ##$$##
            //                      ##



            xwidth-=4;  // Just step back a bit from the last one,
            xoffset = GRID_TEXTURE_WIDTH/2 - (int)floor(xwidth/2); // and recalc this one...
            xoffset += isopos->x;  // add the position of the Tile we're currently looking at


            // Now we're good to go. Do the same thing in loop2 but reverse the operations
            // on xwidth and xoffset for every line:


            fromX = xoffset;


            for(int y = (GRID_TEXTURE_HEIGHT/2); y <= GRID_TEXTURE_HEIGHT; y++)
            {

                // Setup from and to

                toX = fromX + xwidth;

                if(debugLevel >=1 && debugDrawing)
                {

                    // Along the x-pixels we're looking, draw an orange line
                    sf::RectangleShape searchLine(sf::Vector2f(xwidth, 1));

                    drawFromX = fromX + viewHPos->x;
                    drawFromY = currentY + viewHPos->y;


                    searchLine.setPosition(sf::Vector2f( drawFromX,
                                                         drawFromY));



                    searchLine.setOutlineThickness(1.0f);
                    searchLine.setOutlineColor(sf::Color(255,200,0));
                    searchLine.setFillColor(sf::Color(255,200,0));

                    rt.draw(searchLine);
                }


                if( fromX <= searchPos_gpix_x  && searchPos_gpix_x < toX ) {

                    if(currentY == searchPos_gpix_y) {

                        // inside?
                        if(debugLevel >=1) {std::cout << ind << " - - -  Eureka!  we are inside " << fromX << " - ( " << searchPos_gpix_y << " ) - " << toX << "\n";}
                        return isopos;

                    }
                }

                // No luck, please go down one pixelline and decrease Xwidth and adjust xoffset


                xwidth-=4;

                fromX = isopos->x;
                fromX += GRID_TEXTURE_WIDTH/2;
                fromX -= (int)floor(xwidth/2);      // Does this even work? Correct thinking?


                // Next line? increment currentY
                currentY++;

            }


        }  // for x   iso tiles

    } // for y        iso tiles



    return nullptr;

}
*/
