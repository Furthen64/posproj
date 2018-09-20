#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cmath>
#include <time.h>
#include <random>
#include <cerrno>
#include <cstring>
#include <clocale>
#include "ScreenPos.hpp"
#include "CanvasPos.hpp"
#include "../../src/Singletons/Logger.hpp"
#include "../../src/Singletons/WindowSingleton.hpp"


#define PI 3.1415926535897932


#ifdef __linux__
    #include <unistd.h>
    #define getCurrentDir getcwd
#elif _Win32_
    #include <direct.h>
    #define getCurrentDir _getcwd
#endif



int **allocateMatrix(int rows, int cols);
void dumpMatrix(int** matrix, int rows, int cols, std::string);
int **copySubMatrix(int **srcMtx, int srcRows, int srcCols, int startY, int startX, int height, int width,int debugLevel);
void initRandomizer();
int randBetween(int lowNr, int highNr);
void waitForInput();
std::string getFullUri(std::string relativeUri);
void logErr (std::string str);
void logWarn (std::string str);
void hlog (std::string str);



// GL Utils, rotating and scaling ormatrix to an isomatrix, and back
// and for knowing what a clicked position in an iso tile would be in an OrMatrix
float glConv_x(int windowPos_x);
float glConv_y(int windowPos_y);

float rotateCCW_x(float , float , float angleCCW_deg);
float rotateCCW_y(float , float , float angleCCW_deg);

float rotateCW_x(float , float , float angleCW_deg);
float rotateCW_y(float , float , float angleCW_deg);


// Position Utils
CanvasPos *scrpos_to_cpos(ScreenPos *);
ScreenPos *cpos_to_scrpos(CanvasPos *);

std::string getFullUri(std::string relativeUri);


#endif
