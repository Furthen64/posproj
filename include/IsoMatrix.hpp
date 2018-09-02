#ifndef ISOMATRIX_H
#define ISOMATRIX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "OrMatrix.hpp"
#include "CanvasPos.hpp"
#include "Constants.hpp"

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
