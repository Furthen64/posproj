#ifndef CONSTANTS_H
#define CONSTANTS_H

/// Files

#define DEFAULT_FILENAME "data\\maps\\_default_.txt"


/// Window settings

#define WINDOW_WIDTH_PX 1024
#define WINDOW_HEIGHT_PX 768
#define WINDOW_WIDTH_PX_CENTER (WINDOW_WIDTH_PX/2)
#define WINDOW_HEIGHT_PX_CENTER (WINDOW_HEIGHT_PX/2)

#define ORMATRIX_TILE_HEIGHT_PX 46      // These nrs are from doing a scale of height only 198% of the isometric grid, and then doing a 45 deg left rotation
#define ORMATRIX_TILE_WIDTH_PX  46      // what I ended up with was a square matrix with tiles size of 46 x 46 px


const int NR_GRIDS_HEIGHT = 20;            // Seems fine to change this to 20x20,  32x32 or 64x64 , havent made 20x40 to work tho... like a rectangle
const int NR_GRIDS_WIDTH  = 20;

const int GRID_TEXTURE_HEIGHT = 32;
const int GRID_TEXTURE_WIDTH  = 64;

const int GAMEMATRIX_MAX_ROWS = 512;
const int GAMEMATRIX_MAX_COLS = 512;
#endif
