#ifndef ISOMATRIX_H
#define ISOMATRIX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "IsoRect.hpp"
#include "LineRect.hpp"
#include "OrMatrix.hpp"
#include "CanvasPos.hpp"
#include "Constants.hpp"

class IsoMatrix
{
public:
    IsoMatrix();
    IsoMatrix(OrMatrix *);
    IsoMatrix(int _rows, int _cols);


    void drawAll(sf::RenderTarget& rt);
    void setTopLeft(int , int );
    void setTopLeft(CanvasPos *);
    void setPosByNewMiddle(CanvasPos *);

    void moveToOrigo();
    void moveByTopLeftSaveMiddle(CanvasPos *);
    void moveBack();

    void scale_y(float scaleFactor);
    void rotateNDegCCW(float n);
    void rotateNDegCW(float n);

    CanvasPos *getMiddle_cpos();
    CanvasPos *getTopLeft_cpos();
OrMatrix *getOrMatrix();
int getRows();
int getCols();


int getWidthPx();
int getHeightPx();

bool isPosInsideGameMatrix(CanvasPos *);

void calculatePxBounds();

IsoRect *getIsoRect();




private:
    std::string cn = "IsoMatrix.cpp";
    CanvasPos *topleft;
    CanvasPos *prev_cpos;
    OrMatrix *orMat;    // The parent matrix object
    LineRect *lrect;

    int cols;
    int rows;

    sf::Sprite sprite;
    sf::Texture texture;

    int minX = 7870;
    int minY = 7870;


};




#endif
