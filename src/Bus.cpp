#include "Bus.hpp"
#include "RoadNetwork.hpp"

#include "Utilities/Utils.hpp"
#include "HView.hpp"


// Seems to work
// (-+)
Bus::Bus()
{


    logErr("bus POSITIONS needs serious reconsidering. Should it have a CanvasPos and an IsoPos? How are the two synched? lot of functions to go over. \n");
    slotPath = nullptr;

    // Setup texture and sprite
    ResourceHolder *res;
    res = res->getInstance();




    texture = res->getTexture("BUS001");
    sprite = sf::Sprite(texture);
    textureSize = sprite.getTextureRect();
}



// (--)
void Bus::reset()
{
    if(slotPath != nullptr) { delete slotPath; }
    slotPath = nullptr;

    // Ignore texture stuff, probably wont change since construction
}















///
/// TRAFFIC FUNCTIONS
///



/// \brief Takes roadnetwork the bus is on as argument,
///  So whenever the bus needs to move to a new road it can use the correct iso offsets for that particular roadnetwork
// (--) test more... remove unecessary stuff
void Bus::gameUpdate(RoadNetwork *roadnet)
{


    // problem with:         this->pos = Grid::convert_gpix_to_iso(this->pos);



    logErr("bus gameupdate stub\n");

    /*
    SlotPos *workPosGpix;
    CanvasPos *tempPos = new CanvasPos();

    if(slotPath->hasValues()) {

        // make the bus use its slotpath

        workPosGpix = slotPath->stepAndGetGpixPos(1);   // Make 1 step

        if(workPosGpix == nullptr) {
            std::cout << "ERROR " << cn << " gameUpdate tried getting a slotPos from slotPath but ended up with a nullptr. \n";
            return ;
        }


        // Update current Pos
        this->pos = workPosGpix->hpos;

        this->pos->xmid = this->pos->x;       // Ugh.. make sure the right gpix values are set
        this->pos->ymid = this->pos->y;

        this->pos = Grid::convert_gpix_to_iso(this->pos);


        // FIXME: std::cout << "ERROR " << cn << " gameUpdate() Make sure we get iso position too!";

        this->pos = tempPos;

    }
    */
}







// (-+)
void Bus::draw( sf::RenderTarget& rt, int drawSlotPositions)
{

    if(drawSlotPositions) {
        slotPath->drawAllSlots(rt);
    }

    WindowSingleton *win;
    win = win->getInstance();

    int x = pos->x + win->hview->getTopLeft_x();
    int y = pos->y + win->hview->getTopLeft_y();

    sf::Vector2f _pos = {(float)x,(float)y};

    sprite.setPosition(_pos);           // OPTIMA: You could optimize by sending a reference/pointer, reuse the same workposition inside the Bus object

    rt.draw( sprite );
}






 ///
 ///    Random utilities
 ///




/// @brief Gives you a random iso position from the gamematrix
/// @param maxM  Maximum in M or Y axis
/// @param maxN  Maximum in N or X axis
/// (--)
IsoPos *Bus::rand_iso_pos(int maxM, int maxN)
{
    int m = randBetween(0, maxM);
    int n = randBetween(0, maxN);

    IsoPos *_iso_pos = new IsoPos(m,n);
    return _iso_pos;
}














/// \brief Randomize an iso position on the RoadNetwork, use the Y and X offset to figure out the absolute position on the gamematrix
/// \param roadnet
// (---) TESTME alpha-0.2

IsoPos *Bus::rand_abs_iso_pos(RoadNetwork *roadnet)
{
    // Deal with rect
    logErr("bus rand abs iso pos stub \n");


    /*
    // Error check input
    if(roadnet->nrRows() > 10000 || roadnet->nrCols() > 10000) {
        std::cout << "ERROR" << cn << " too big of a roadmatrix! " << roadnet->hMatrix->rows << ", " << roadnet->hMatrix->cols << "\n";
        return nullptr;
    }

    // Try and find a random position inside the roadnetwork

    bool found = false;
    int allowedAttempts = 500;
    int currAttempt = 0;

    IsoPos *newPos = new IsoPos(0,0);

    int r = 0;
    int c = 0;

    while(found == false && currAttempt < allowedAttempts)
    {

        r = randBetween(0, roadnet->nrRows()-1);
        c = randBetween(0, roadnet->nrCols()-1);

        if(roadnet->hMatrix->matrix[r][c] == 1) {


            newPos->y = r + roadnet->rect->absStart->y;
            newPos->x = c + roadnet->rect->absStart->x;

            found = true;

        }

        currAttempt++;

    }


    if(found == false) {
        logWarn(cn + " rand_abs_iso_pos could not find a position.\n");
        return nullptr;
    }

    return newPos;
    */

    return nullptr;
}



// (-+)
void Bus::setSlotPath(SlotPath *_sp)
{
    if(_sp == nullptr) {
        std::cout << "ERROR " << cn << "trying to set a null slotpath for a bus! bus at= " << pos->dumpToString() << "\n";
    }
    slotPath = _sp;
}





// (--)
void Bus::dump(std::string ind)
{

    std::cout << " --- bus " << pos->dumpToString() << " ------\n";
    std::cout << ind << "slotpath:\n";
    slotPath->dump();
    std::cout << "\n";
}



// (-+)
void Bus::dump()
{
/*
    WindowSingleton *win;
    win = win->getInstance();
    HView *hview = win->hview;


    int wy = hview->getTopLeft_y();
    int wx = hview->getTopLeft_x();
*/
    std::cout << "\n\nBus:\n";
    std::cout << "       y,abs_iso-x     rely,relx        gpix_y,gpix_x     wpix_y,wpix_x\n";
    /*
    std::cout << "   pos           " << pos->y << "," << pos->x << "                    "  << pos->rely << ", " << pos->relx << "                      " << pos->y << "," << pos->x <<  "            " << wy + pos->y << "," << wx + pos->x << "\n";

    std::cout << "   nextPos       " << nextPos->y << "," << nextPos->x << "                    "  << nextPos->rely << ", " << nextPos->relx << "                      " << nextPos->y << "," << nextPos->x <<  "            " << wy + nextPos->y << "," << wx + nextPos->x << "\n\n";
*/
}



// Get internal pointer of what the next position for the bus is
CanvasPos *Bus::get_next_pos()
{
    return nextPos;
}





/// \brief returns pointer to HPos that describes where the Bus is right now. Warning: internal pointer!
// (-+)
CanvasPos *Bus::getNow_cpos()
{
    logErr("bus getNow_cpos stub\n");
/*    if(slotPath->nowPos_gpix != nullptr) {

        return slotPath->nowPos_gpix->hpos;
    }
*/
    return nullptr;
}



/// \brief is bus at given isopos?
// (--)
bool Bus::atPos(IsoPos *search_isopos)
{
    logErr("bus atpos positioning ...\n");
    /*
    CanvasPos *now = getNow_cpos();

    if(now != nullptr) {
        if(now->compareAbsIso(search_isopos) == 0) {
            return true;
        }
    }
*/
    return false;
}
