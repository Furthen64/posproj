#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cmath>
#include <time.h>
#include <random>
#include <cerrno>
#include <cstring>
#include <clocale>



#include "../../src/Singletons/Logger.hpp"


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

float rotate_x(float previous_x, float previous_y, float angleCCW_deg);
float rotate_y(float previous_x, float previous_y, float angleCCW_deg);

#endif
