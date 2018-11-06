#ifndef HURKAMAP_H
#define HURKAMAP_H

#include <list>
#include <string>
#include <SFML/Graphics.hpp>


#include "IsoPos.hpp"

#include "TrafficManager.hpp"           // <= utils.hpp,   <= texturemanager.hpp ,  <= block.hpp

// HurkaMap
// is a container for the std::list<Block *> blockList which we will use to render all the blocks on the board
// The list is just a flat long list of all the Blocks to be rendered. They are put in a particular order for the
// rendering process to draw them layer by layer in an isometric way... hard to explain in text.
// see Docs / Parsing_Matrix_to_BlockList.mp4


// 2018-05-17       jörgen engström         CR15 Making the Matrix size, same size as GameMatrix


class HurkaMap
{
public:

    HurkaMap(std::string _fullUriMapName, int **_matrix, int mtxRows, int mtxCols);
    HurkaMap(int mtxRows, int mtxCols);
    ~HurkaMap();


    void draw(sf::RenderTarget& rt);

    void testList();

    int placeNewOrSwapRoad(IsoPos *roadPos, int debugLevel);
    int placeNewRoad(IsoPos *roadPos, int debugLevel );

    void putBlockList(std::list<Block *> _blockList);

    int indexInBlockList(IsoPos *);
    int **getMatrix();
    int layerNrInBlockList(IsoPos *);
    int getNrBlocks();

    HurkaMatrix *getRoadHMatrix();

    std::string fullUriMapName;


    // Debug utils

    void dumpEverythingAtPos(IsoPos *, TrafficManager *, std::string );
    void dump(std::string);

    int getRows() { return matrixRows; }
    int getCols() { return matrixCols; }

private:

    std::list<Block *> blockList; // All the blocks we render
    std::string cn = "HurkaMap.cpp";
    int **matrix;
    int matrixRows;
    int matrixCols;

};


#endif
