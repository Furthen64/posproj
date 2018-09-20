#ifndef ISORECT_H
#define ISORECT_H

#include <iostream>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include "CanvasPos.hpp"
#include "IsoPos.hpp"


class IsoRect
{

public:

	IsoRect(int _absStartY,
			int _absStartX,
			int _rows,
			int _cols,
			int _heightPx,
			int _widthPx);

    IsoRect(IsoPos *_absStartPos,
			int _rows,
			int _cols,
			int _heightPx,
			int _widthPx);



    IsoRect(IsoPos *_absStartPos, IsoPos *_absEndPos );

    IsoRect();


    // General functions
    bool containsIsoPos(IsoPos *searchPos);

    int nrTiles();

	std::string relToString();
    std::string absToString();

	int compare(IsoRect *other);
    int compareAbsStartPoint(IsoRect *other);
	int compareSize(IsoRect *other);

	bool insideXPixles_middle(CanvasPos *pxPos);
	bool insideYPixles_middle(CanvasPos *pxPos);


	IsoRect *clone();
    void dump(std::string ind);
    void fullDump(std::string ind);





    // Special functions

    void calculateBounds();

    void testFunctions();

    void draw(sf::RenderTarget& rt);





	// The position and sizes
	IsoPos *absStart;
	IsoPos *absEnd;
	int rows;
	int cols;
	IsoPos *relStart;


	// Canvas Boundaries of the rect
	CanvasPos  *topB = nullptr;
	CanvasPos *rightB = nullptr;
	CanvasPos *bottomB = nullptr;
	CanvasPos *leftB = nullptr;





	int heightPx;  // FIXME remove the heightpx and widthpx ?
	int widthPx;




private:

    bool drawable = false ;       // OPTIMIZE set to false for faster IsoRects    , OPTIMIZE further by coding #defines to disable if-checks in draw()

    sf::Texture texture;
    sf::Sprite sprite;


    std::string cn = "IsoRect.cpp";
};

#endif
