#include "Utilities/Utils.hpp"


// Seems to work for a couple of weeks now (2018-04) havent given thoughts about memory DEALLOCATION though...
// (-+)
int **allocateMatrix(int rows, int cols)
{
    std::string cn = "Utils.cpp";

    if(rows > 10000 || cols > 10000) {
            std::cout << "ERROR " << cn << " Cannot allocate matrix of that size! " << rows << ", " << cols << "\n";
        return nullptr;
    }

    int** matrix = new int*[rows];
    if (rows)
    {
        matrix[0] = new int[rows * cols];
        for (int i = 1; i < rows; ++i)
            matrix[i] = matrix[0] + i * cols;
    }


    // Set all values in the matrix to 0
    for(int r = 0; r < rows; r++) {

        for(int c = 0; c < cols; c++) {
                matrix[r][c] = 0;

        }
    }




    return matrix;

}



// (++)
void dumpMatrix(int** matrix, int rows, int cols, std::string indent)
{

    std::string cn = "Utils.cpp";

    if(rows > 10000 || cols > 10000) {
        std::cout << indent << "ERROR" << cn << " too big of a roadmatrix! " << rows << ", " << cols << "\n";
        return ;
    }


    std::cout << "\n\n" << indent << "Matrix: \n" << indent  << "{\n" << indent;
    for(int r = 0; r < rows; r++) {
        std::cout << "   ";
        for(int c = 0; c < cols; c++) {
                std::cout << matrix[r][c] << ", ";

        }
        std::cout << "\n" << indent;
    }
    std::cout << "}\n";


}



// Takes  a matrix (srcMtx) with its srcRows x srcCols
// Starts at row startY, column startX and copies height x width block of data from that matrix into a new one, returns new one.
//
// TESTED a few times, works fine
// Docs: Utils_copySubMatrix.png
// BUG: startx starty is wrong
// (-+)
int **copySubMatrix(int **srcMtx, int srcRows, int srcCols, int startY, int startX, int height, int width, int debugLevel)
{

    std::string cn = "Utils.cpp";

    if(debugLevel >=1) {
        std::cout << "\n\ncopySubMatrix\n----------------\n";
        std::cout << "srcRows=" << srcRows << ", srcCols=" << srcCols << ", startY=" << startY << ", startX=" << startX << ", height=" << height << ", width=" << width << "\n";
    }

    if(srcMtx == nullptr) {
        std::cout << "ERROR " << cn << " supplied nullptr to copySubMatrix!\n";
        return nullptr;
    }

    if(startY > srcRows) {
        std::cout << "ERROR " << cn << " startY > srcRows in copySubMatrix!\n";
        return nullptr;
    }

    if(startX > srcCols) {
        std::cout << "ERROR " << cn << " startX > srcCols in copySubMatrix!\n";
        return nullptr;
    }


    if( (startY + height) > srcRows) {
        std::cout << "ERROR " << cn << " (startY+height) > srcRows in copySubMatrix!\n";
        return nullptr;
    }



    if( (startX + width) > srcCols) {
        std::cout << "ERROR " << cn << " (startX+width) > srcCols in copySubMatrix!\n";
        return nullptr;
    }


    if(debugLevel >=2) {
        std::cout << "dumping srcmtx:\n";
        dumpMatrix(srcMtx, srcRows, srcCols, "   ");

    }



    /// Allocate the new matrix
    int **destMtx = nullptr;

    destMtx = allocateMatrix(height, width);



    /// Loop over original matrix and do the work
    if(debugLevel >=2) {
        std::cout << " Looping original matrix, copying only the parts we want:\n";
    }

    for(int srcY = startY, destY = 0; srcY < (startY+height); srcY++, destY++)
    {
        for(int srcX = startX, destX = 0; srcX < (startX+width); srcX++, destX++)
        {

            if(debugLevel >=2) {
                std::cout << "   srcMtx[" << srcY << "][" << srcX << "]";
                std::cout << "   destMtx[" << destY << "][" << destX << "]    = " << srcMtx[srcY][srcX] << "\n\n";
            }

            destMtx[destY][destX] = srcMtx[srcY][srcX]; // Copy the value from the original

        }
    }



    return destMtx;

}


void logErr (std::string str)
{
    // Check global errno too

    if(errno == EDOM) {
        std::cout << "ERROR errno is set=" << std::strerror(errno) << "\n";
    }
    errno = 0;

    // Open up the Logger singleton and write to file
    Logger *logger;
    logger = logger->getInstance();

    logger->logError(str);
}



float rotate_x(float previous_x, float previous_y, float angleCCW_deg)
{
    float retval = previous_x * cos(angleCCW_deg) - previous_y * sin(angleCCW_deg);     // See https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm
    return retval;
}


float rotate_y(float previous_x, float previous_y, float angleCCW_deg)
{
    float retval = previous_y * cos(angleCCW_deg) + previous_x* sin(angleCCW_deg);
    return retval;
}
