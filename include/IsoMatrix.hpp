#ifndef ISOMATRIX_H
#define ISOMATRIX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "OrMatrix.hpp"
#include "CanvasPos.hpp"
#include "Constants.hpp"

/// The IsoMatrix is basically the gameboard in its rectangular form.
/// Game logic happens in the IsoMatrix.
/// You can draw the IsoMatrix and see what's going on with all the objects and their positions. Quite a good thing for developers!
/// The IsoMatrix can be converted into an IsoMatrix, the gameboard you see when playing the game. See "IsoMatrix.hpp"

class IsoMatrix
{
public:
    IsoMatrix();
    IsoMatrix(OrMatrix *);
    void drawAll(sf::RenderTarget& rt);
    void setPosition(CanvasPos *cpos);


private:
    std::string cn = "IsoMatrix.cpp";
    CanvasPos *topleft;
    OrMatrix *orMat;    // The parent matrix object

};




#endif
