#ifndef GRID_H
#define GRID_H

#include <sstream>
#include <assert.h>

#include <SFML/Graphics.hpp>


#include "../src/Singletons/WindowSingleton.hpp"
#include "CanvasPos.hpp"
#include "OrMatrix.hpp"
#include "OrPos.hpp"
#include "IsoPos.hpp"
#include "CRect.hpp"
#include "Constants.hpp"
#include "Utilities/Utils.hpp"




/// Contains the Grid, but also a selected grid piece that will light up, allowing for selecting or something
///
///
class Grid
{
public:

    Grid() {}
    Grid(int _height, int _width);

    void draw( sf::RenderTarget& rt);

    void setSelectedTile(CanvasPos *);

    void hideSelectedTile();

    // Search function
    //IsoPos *findTile(HRect *entireGameBoard, CanvasPos *searchpos_gpix_middle, std::string ind, sf::RenderTarget& rt, std::string recursionName);






// If you look at the gamematrix like this:
//
//
//                           (0,0)
//                       (1,0)   (0,1)
//                    (2,0)  (1,1)  (0,2)
//                  (3,0) (2,1) (1,2) (0,3)
//
// You could put a layernr on each layer  (each new line here in this asciiart)
//
//
//
//   Layer0                  (0,0)
//   Layer1              (1,0)   (0,1)
//   Layer2           (2,0)  (1,1)  (0,2)
//   Layer3         (3,0) (2,1) (1,2) (0,3)
//   ...
//
// That's what this function does, it finds out on what layer a particular HPos would be.
//
// Wishlist: Please synch this with the readRegularFile .... needs to copy this documentation to that one

/// \brief Finds out on what layer to render a particular block, given its HPos position
/// \param searchPos IsoPos
/// \return returns the layernr when found, -1 otherwise.
// (--)     Seems to work fine! but moved from somewhere else to here 2018-08-12, so needs testing again! :)
static int layerNrInBlockList(IsoPos *searchPos)
{

    int debugLevel = 0;

    int matrixRows = NR_GRIDS_HEIGHT;   // Hardcoded fixme
    int matrixCols = NR_GRIDS_WIDTH;


    // we know the  Y max in this shiiiit
    // make loop1 and loop2 like in "readRegularFile"

    // If you generate a whole isometric gamematrix again... like from a matrix
    // you could easily tell where a HPos would be , because you'd have all positions..
    //

    // So you STOP when you hit that HPos


    int layerNr = 0;
    IsoPos *workPos = nullptr;
    std::string searchPosStr = searchPos->absToString();
    std::string ind1 = "   ";



    // Loop 1:
    int yDown = 0;
    int yUp = 0;
    int xRight = 0;



    // Loop 2:
    int xDownRight = 0;

    if(debugLevel >=1) {
        std::cout << "\n\n* layerNrInBlockList()\n{";
        std::cout << ind1 << " - matrix size(: " << matrixRows << ", matrixCols: " << matrixCols << "\n\n";
        std::cout << ind1 << " - layerNr:" << layerNr << "\n";

        std::cout << "\n\n" << ind1 << " - loop1:      \n" << ind1 << "----------\n";
    }

    while(yDown < matrixRows)
    {
        while(yUp > -1 && xRight < matrixCols)
        {

            // matrix coordinates:
            //   row = yUp
            //   col = xRight

            workPos = new IsoPos( yUp, xRight);

            if(debugLevel >= 2) { std::cout << ind1 << "At= " << workPos->absToString() << " vs Search=" << searchPosStr << " \n"; }


            if(workPos->compareAbsIso(searchPos) == 0) {
                if(debugLevel >=1) { std::cout << ind1 << "   Match found!\n"; }
                return layerNr;
            }


            yUp--;
            xRight++;
        }



        layerNr++;
        if(debugLevel >=1) { std::cout << ind1 << "layerNr=" << layerNr << "\n"; }


        // Go down the matrix in the Y axis
        yDown++;

        // Reset x iterator
        xRight = 0;

        // Now yUp starts a step lower down
        yUp = yDown;
    }


    if(debugLevel >=1) {

        std::cout << ind1 << "\n\nLoop2:\n" << ind1 << "-------------\n";
        std::cout << ind1 << "layerNr=" << layerNr << "\n";
    }


    yUp = matrixRows-1; // Start at the Bottom Left

    xDownRight++;

    xRight = xDownRight;

    while(xDownRight < matrixCols)
    {
        while(yUp > -1 && xRight < matrixCols)
        {
            workPos = new IsoPos(yUp, xRight);

            if(debugLevel >=2) {std::cout << ind1 << "At= " << workPos->absToString() << " vs Search=" << searchPosStr << " \n";}

            if(workPos->compareAbsIso(searchPos) == 0) {

                if(debugLevel >=1) { std::cout << ind1 << "   Match found!\n"; }

                return layerNr;
            }

            yUp--;      // going upwards...
            xRight++;   // ...and right

        }

        layerNr++;
        if(debugLevel >=1) { std::cout << ind1 << "layerNr=" << layerNr << "\n";}

        xDownRight++;

        xRight = xDownRight;
        yUp = matrixRows -1;
    }



    if(debugLevel >=1) { std::cout << "\n}\n\n"; }



    // We did not find anything
    return -1;
}





/// \param typeOfElement 0=GRID, 1=GAMEMATRIX,  2=BLOCK
// (--)     test for Blocks of different sizes
static int isoToGpixMiddleY(IsoPos *iso_pos, int typeOfElement, int _debugLevel)
{


    logErr("isoToGpixMiddleY typeOfElement no longer needed\n");
    std::string cn = "Grid.hpp";

    assert(iso_pos != nullptr);

    int height = GRID_TEXTURE_HEIGHT;

    int X = iso_pos->x;
    int Y = iso_pos->y;

    int globalYOffset= 500;
    int globalXOffset= 1500;
    int initialYOffset = 0;
    int initialXOffset = 0;
    int yOffset = 0;
    int xOffset = 0;
    int yStep = 0;




    if(_debugLevel >=1) {
        std::cout << "\n\niso to gpix middle Y--------------------------\n";
    }

    if(typeOfElement == 0 || typeOfElement == 1) {

        //
        // Grid or Gamematrix, let's see if we can put this in the right spot on the gameboard
        //

        initialYOffset = globalYOffset + GRID_TEXTURE_HEIGHT;
        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_HEIGHT);

        if(_debugLevel >=1) {
            std::cout << "initialYOffset=" << initialYOffset << "\n";
            std::cout << "initialXOffset=" << initialXOffset << "\n";
        }

        yOffset = initialYOffset;
        xOffset = initialXOffset;


        // Allright, so we're gonna do this in two loops.
        // The first loop goes step by step down the Y ladder (down left on the y axis)

        for(int yNr = 0; yNr < Y; yNr++) {

            yOffset += (GRID_TEXTURE_HEIGHT/2);
            xOffset -= (GRID_TEXTURE_WIDTH/2);

        }


        // Next loop, we go inwards the pyramid (down right on the x axis)


        for(int xNr = 0; xNr < X; xNr++) {


                yOffset += (GRID_TEXTURE_HEIGHT/2);
                xOffset += (GRID_TEXTURE_WIDTH/2);

        }


    } else if(typeOfElement == 2) {


        // BLOCK

        // alpha-0.2: not sure this one works as well as it should anymore.

         initialYOffset = globalYOffset + 0;     // Start at the top

         yOffset = initialYOffset;


         yStep = 0;

        if(height < GRID_TEXTURE_WIDTH) {
            // Smaller, IF the sprite height is less than the 64 GRID height we have to move it down
            // the division by 4 is now division by 2

            yStep =  (Y*GRID_TEXTURE_WIDTH/4) + (X*GRID_TEXTURE_WIDTH/4) + 32;

        } else if(height > GRID_TEXTURE_WIDTH) {
            // Taller, like high buildings, make sure you start drawing HIGHER (lower y value)
             yStep = (Y*GRID_TEXTURE_WIDTH/4) - (X*GRID_TEXTURE_WIDTH/4);

        } else {
            // (++)
            // Equal to the grid size
            yStep = (Y*GRID_TEXTURE_WIDTH/4) + (X*GRID_TEXTURE_WIDTH/4);
        }

    }


    return yOffset + yStep + (GRID_TEXTURE_HEIGHT/2);
}







/// \param typeOfElement 0=GRID, 1=GAMEMATRIX,  2=BLOCK
// (--) Completely rewritten, please test
// Wishlist: Please make this smarter, prettier, more beautiful, a wonder to watch, something delightful!
//           right now it has a weird name, and I don't like the wonky iso_pos gpix jumping around within the same HPos..
static int isoToGpixMiddleX(IsoPos *iso_pos, int typeOfElement, int _debugLevel)
{

    assert(iso_pos != nullptr);

    int X = iso_pos->x;
    int Y = iso_pos->y;

    int width = GRID_TEXTURE_WIDTH;

    int globalYOffset= 500;
    int globalXOffset= 1500;
    int initialYOffset = 0;
    int initialXOffset = 0;
    int yOffset = 0;
    int xOffset = 0;
    int xStep = 0;

    if(_debugLevel >=1) {
        std::cout << "\n\niso to gpix middle X--------------------------\n";
    }


    if(typeOfElement == 0 || typeOfElement == 1) {


        //
        // Grid or Gamematrix, let's see if we can put this in the right spot on the gameboard
        //

        initialYOffset = globalYOffset + GRID_TEXTURE_HEIGHT;
        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_HEIGHT);

        if(_debugLevel >=1) {
            std::cout << "initialYOffset=" << initialYOffset << "\n";
            std::cout << "initialXOffset=" << initialXOffset << "\n";
        }

        yOffset = initialYOffset;
        xOffset = initialXOffset;


        // Allright, so we're gonna do it in two loops
        // First loop goes step by step down the Y ladder (down left on the y axis)

        for(int yNr = 0; yNr < Y; yNr++) {

            yOffset += (GRID_TEXTURE_HEIGHT/2);
            xOffset -= (GRID_TEXTURE_WIDTH/2);

        }



        if(_debugLevel >=1) {
            std::cout << " now at: 612,1660 ?    (" << yOffset << ", " << xOffset << ")\n";
        }



        // Next loop, we go inwards the pyramid (down right on the x axis)


        for(int xNr = 0; xNr < X; xNr++) {


                yOffset += (GRID_TEXTURE_HEIGHT/2);
                xOffset += (GRID_TEXTURE_WIDTH/2);

        }


        if(_debugLevel >=1) {
            std::cout << " finally at: 644,1724 ?    (" << yOffset << ", " << xOffset << ")\n";
        }




    } else if (typeOfElement == 2) {


        /// BLOCK

        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_WIDTH);   // Make sure we place everything in the x-positive euclidian space


        /// Calculate the X-offset
        // intialXOffset - where we are in the height=M index TIMES the sprite_width/2
        xOffset = initialXOffset - ((iso_pos->y)*(GRID_TEXTURE_WIDTH/2));


        // now for every step to the right=N index we have to go right a bit

        // TODO: adjust for small width textures! all mine are 64 so... I need more examples
        xStep = (iso_pos->x)*(width/2);


    }

    return xOffset + xStep + (GRID_TEXTURE_WIDTH/2);


}




// DOCS: see "GameMatrix_How_the_x_position_is_calculated.png"
// N = along the right-down axis
// M = along the left-down axis of the gameboard
// width = width of the texture
// height = height of the texture
// typeOfElement        0,1     =   GRID or GAMEMATRIX
//                        2     =   BLOCK


// (--)
static int convert_iso_to_x(int M, int N, int width, int height, int typeOfElement)
{

    std::string cn = "Grid.hpp";

    if(width == 0 || height == 0) {
        std::cout << "ERROR " << cn << " height or width = 0 in call to convert_iso_to_pix_x!!\n";
        return -1;
    }

    /*int globalXOffset= 1500;
    int initialXOffset = 0;*/
    int globalXOffset= 0;
    int initialXOffset = 0;
    int xOffset = 0;
    int xStep = 0;

    if(typeOfElement == 0 || typeOfElement == 1) {

        /// GRID or GAMEMATRIX
        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_HEIGHT);   // Make sure we place everything in the x-positive euclidian space


        // Calculate the X-offset
        // intialXOffset - where we are in the height=M index TIMES the sprite_width/2
        xOffset = initialXOffset - M*(GRID_TEXTURE_WIDTH/2);


        // now for every step to the right=N index we have to go right a bit

        // TODO: adjust for small width textures! all mine are 64 so... I need more examples
        xStep = N*(width/2);




    } else if (typeOfElement == 2) {


        /// BLOCK

        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_WIDTH);   // Make sure we place everything in the x-positive euclidian space


        /// Calculate the X-offset
        // intialXOffset - where we are in the height=M index TIMES the sprite_width/2
        xOffset = initialXOffset - M*(GRID_TEXTURE_WIDTH/2);


        // now for every step to the right=N index we have to go right a bit

        // TODO: adjust for small width textures! all mine are 64 so... I need more examples
        xStep = N*(width/2);


    }


    return xOffset + xStep;
}





/// \param M = along the left-down axis of the gameboard
/// \param N = along the right-down axis
/// \param width = width of the texture
/// \param height = height of the texture
/// \param typeOfElement 0=GRID, 1=GAMEMATRIX, 2=BLOCK
// DOCS: see "GameMatrix_How_the_y_position_is_calculated.png"

static int convert_iso_to_y(int M, int N, int width, int height, int typeOfElement)
{

    if(width == 0 || height == 0) {
        std::cout << "ERROR grid.hpp height or width = 0 in call to convert_iso_to_pix_y!!\n";
        return -1;
    }


    int Y = M;
    int X = N;

    int globalYOffset= 0;
    int globalXOffset= 0;

    int initialYOffset = 0;
    int initialXOffset = 0;
    int yOffset = 0;
    int xOffset = 0;
    int yStep = 0;



    if(typeOfElement == 0 || typeOfElement == 1) {


        /// Grid or Gamematrix, let's see if we can put this in the right spot on the gameboard


        initialYOffset = globalYOffset + GRID_TEXTURE_HEIGHT;
        initialXOffset = globalXOffset + (GRID_TEXTURE_WIDTH / 4 * NR_GRIDS_HEIGHT);


        yOffset = initialYOffset;
        xOffset = initialXOffset;


        // Allright, so we're gonna do this in two loops.
        // The first loop goes step by step down the Y ladder (down left on the y axis)

        for(int yNr = 0; yNr < Y; yNr++) {

            yOffset += (GRID_TEXTURE_HEIGHT/2);
            xOffset -= (GRID_TEXTURE_WIDTH/2);

        }


        // Next loop, we go inwards the pyramid (down right on the x axis)

        for(int xNr = 0; xNr < X; xNr++) {
                yOffset += (GRID_TEXTURE_HEIGHT/2);
                xOffset += (GRID_TEXTURE_WIDTH/2);
        }

        yStep = 0;


    } else if(typeOfElement == 2) {

        ///BLOCK

         initialYOffset = globalYOffset + 0;     // Start at the top

         yOffset = initialYOffset;


         yStep = 0;

        if(height < GRID_TEXTURE_WIDTH) {
            // Smaller, IF the sprite height is less than the 64 GRID height we have to move it down
            // the division by 4 is now division by 2

            yStep =  (M*GRID_TEXTURE_WIDTH/4) + (N*GRID_TEXTURE_WIDTH/4) + 32;

        } else if(height > GRID_TEXTURE_WIDTH) {
            // Taller, like high buildings, make sure you start drawing HIGHER (lower y value)
             yStep = (M*GRID_TEXTURE_WIDTH/4) - (N*GRID_TEXTURE_WIDTH/4);

        } else {
            // (++)
            // Equal to the grid size
            yStep = (M*GRID_TEXTURE_WIDTH/4) + (N*GRID_TEXTURE_WIDTH/4);
        }
    }


    return yOffset + yStep;

}



// The new and improved way of converting from Iso Position to Canvas Position!
// see also ctoi
static CanvasPos *itoc(IsoPos *isopos)
{
    WindowSingleton *win;
    win = win->getInstance();

    CanvasPos *cpos;

    int cposY = Grid::convert_iso_to_y( isopos->y, isopos->x, 64, 32, 2);
    int cposX = Grid::convert_iso_to_x( isopos->y, isopos->x, 64, 32, 2);


    cpos = new CanvasPos(cposY,cposX);


    return cpos;
}




/// \brief Converts from a CanvasPos to an Orthogonal Matrix Position
/// \return returns an indexed position (OrPos) if found, nullptr when not found inside the OrMatrix
// (--)
static OrPos *ctoor(CanvasPos *cpos, OrMatrix *orMat1)
{

    // how large are each tile?
    // each tile is ORMATRIX_TILE_WIDTH_PX pixels wide and ORMATRIX_TILE_HEIGHT_PX high
    // so we can divide and see how many tiles we have wandered to the right (x-axis) and then check y-axis

    int y_nrOfTiles = (int) floor(cpos->y / ORMATRIX_TILE_HEIGHT_PX);

    if(cpos->y < orMat1->getTopLeft_cpos()->y) {
            return nullptr;
    }
    if(cpos->x < orMat1->getTopLeft_cpos()->x) {
            return nullptr;
    }

    if(y_nrOfTiles > (orMat1->getRows()-1) )
    {
        return nullptr;
    }

    int x_nrOfTiles = (int) floor(cpos->x / ORMATRIX_TILE_WIDTH_PX);

    if(x_nrOfTiles > (orMat1->getCols()-1)) {
        return nullptr;
    }

    // how many tiles are there
    return new OrPos(y_nrOfTiles,x_nrOfTiles);

}


static IsoPos *ortoi(OrPos *clicked_orpos)
{
    return new IsoPos(-1,-1);
}

private:



    sf::Texture texture;
    sf::Texture textureSelected;
    sf::Sprite sprite;
    sf::Sprite spriteSelected;

    sf::Vector2f selectedTile_vec2f;
    bool drawSelectedTile = false;


    int rows;
    int cols;
    CRect *boundingBox = nullptr;       // Used to move this around and to know the x and y offset to origo
    CanvasPos *topLeft_cpos = nullptr;      // The x and y offset from origo


    sf::Font font;
    sf::Text text;
    sf::Text visibleGridText;

    std::string cn = "Grid.cpp";



    // Search Functions
 /*   IsoPos *findTile(HRect *entireGameboard, HRect *relRect, CanvasPos *searchpos_gpix_middle, std::string ind, int counter, sf::RenderTarget &rt, std::string recursionName, int debugLevel);

    IsoPos *bruteForceFindTile(HRect *entireGameboard, HRect *relRect, CanvasPos *searchpos_gpix_middle, std::string ind, sf::RenderTarget &rt,std::string recursionName, int debugLevel);
    */




};



#endif

