#ifndef ORMATRIX_H
#define ORMATRIX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Constants.hpp"

/// The OrMatrix is basically the gameboard in its rectangular form.
/// Game logic happens in the OrMatrix.
/// You can draw the OrMatrix and see what's going on with all the objects and their positions. Quite a good thing for developers!
/// The OrMatrix can be converted into an IsoMatrix, the gameboard you see when playing the game.


class OrMatrix
{
public:
    OrMatrix();
    OrMatrix(int,int);
    void drawAll(sf::RenderTarget& rt);
    bool isAllocated();

private:
    std::string cn = "OrMatrix.cpp";

    int **matrix = nullptr;
    bool allocated = false;
    int rows = 0;
    int cols = 0;
};




#endif
