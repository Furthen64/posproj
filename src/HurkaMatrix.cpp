#include "HurkaMatrix.hpp"

HurkaMatrix::HurkaMatrix(int _rows, int _cols)
{
    if(_rows < 0 || _cols < 0) {
        std::cout << "ERROR " << cn << " Cannot create a matrix with rows=" << _rows << ", cols=" << _cols << "!\n";
        return ;
    }

    matrix = allocateMatrix(_rows, _cols);
    rows = _rows;
    cols = _cols;
    allocated = true;
}

HurkaMatrix::~HurkaMatrix()
{

}





/// \brief Is the searchpos a road in this hurkamatrix? (where 1=road, 0= something else)
/// \return true if road is in matrix, false otherwise
 // (--) test
bool HurkaMatrix::roadAtRelPos(IsoPos *searchpos, int debugLevel)
{

    if(searchpos->rely < 0) {
        if(debugLevel >=1) {
            std::cout << "ERROR " << cn << " providing rely < 0\n";
        }
        return false;
    }


    if(searchpos->relx < 0) {
        if(debugLevel >=1) { std::cout << "ERROR " << cn << " providing relx < 0\n"; }
        return false;
    }



    if(searchpos->rely > (rows-1)) {
        if(debugLevel >=1) { std::cout << "clicked position cannot be in this roadnet,  providing rely > (matrix.rows-1)       (" << searchpos->rely << " vs " << (rows-1) << "!\n"; }
        return false;
    }


    if(searchpos->relx > (cols-1)) {
        if(debugLevel >=1) { std::cout << "clicked position cannot be in this roadnet,  providing relx > (matrix.cols-1)       (" << searchpos->relx << " vs " << (cols-1) << "!\n"; }
        return false;
    }


    if(matrix[searchpos->rely][searchpos->relx] == 1)
    {
        return true;
    }

    return false;
}






// (++)
void HurkaMatrix::dump(std::string indent)
{
   dumpMatrix(matrix, rows, cols, indent);
}

void HurkaMatrix::dump()
{
   dumpMatrix(matrix, rows, cols, "");
}




