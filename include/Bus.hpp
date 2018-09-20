#ifndef BUS_H
#define BUS_H

#include <SFML/Graphics.hpp>

class RoadNetwork;


#include "IsoMatrix.hpp"
#include "HurkaMatrix.hpp"
#include "Block.hpp"
#include "Grid.hpp"

#include "BusRoute.hpp"
#include "SlotPath.hpp"

class Bus
{
public:

    Bus();


    void reset();
    void gameUpdate(RoadNetwork *roadnet);
    void draw( sf::RenderTarget& rt, int drawSlotPositions);

    void dump(std::string );
    void dump();


    /// Position
    bool atPos(IsoPos *);

    CanvasPos *getNow_cpos();

    void setRandStartingPosition(HurkaMatrix *roadMatrix);


    /// SlotPath and SlotPositions

    void setSlotPath(SlotPath *_sp);

    void setNeedsPlanning() { needsPlanning = true; }
    void resetNeedsPlanning() { needsPlanning = false; }



    /// Random Utilities

    IsoPos *rand_iso_pos(int maxM, int maxN);
    IsoPos *rand_abs_iso_pos(RoadNetwork *roadnet);
    CanvasPos *get_next_pos();




private:

    BusRoute busRoute;        // wishlist: Contains high level route plan for the bus, going from station to station
    SlotPath *slotPath;       // Current Path for the bus

    bool needsPlanning = false;



    CanvasPos *pos;                // Current position, used by draw() and gameUpdate()
    CanvasPos *nextPos;


    sf::Texture texture;
    sf::IntRect textureSize;
    sf::Sprite sprite;

    std::string cn = "Bus.cpp";
};

#endif
