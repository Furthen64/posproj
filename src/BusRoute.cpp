#include "BusRoute.hpp"


BusRoute::BusRoute()
{
    positions = new std::list<IsoPos  *>();
}


// True if the bus is at the this given position, False otherwise
bool BusRoute::isAt_iso_pos(IsoPos  *_pos)
{
    std::cout << "NOT CODED\n";
    return false;
}



IsoPos  *BusRoute::getNext_iso_pos()
{
    std::cout << "NOT CODED\n";
    return nullptr;
}

CanvasPos *BusRoute::getNext_pix_pos()
{
    std::cout << "NOT CODED\n";
    return nullptr;
}


