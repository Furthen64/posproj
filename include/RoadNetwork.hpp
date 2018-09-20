#ifndef ROADNETWORK_H
#define ROADNETWORK_H

#include <list>
#include <string>


#include "Graph.hpp"
#include "Bus.hpp"
#include "HurkaMatrix.hpp"


/// Created by TrafficManager
/// Used by Bus
///
/// A bus rides on a particular Road Network
/// A road network is basically a matrix of the interconnected roads
/// It also contains a rect to tell you where in the gamematrix it is

/// See docs: road_networks.png




class RoadNetwork
{
public:

    RoadNetwork();



    // Generic functions

    int ** getMatrix();

    void clearResources();

    IsoPos *getNrRoad_iso(int findNr, int);

    Bus *busAtPos(IsoPos *searchPos);

    SlotPath *createSlotPath(IsoPos *fromPos, IsoPos *toPos, int debugLevel);

    void createGraphFromHMatrix(HurkaMatrix *roadMatrix,
                                 Graph *graph,
                                 Node *currNode,
                                 Node *prevNode,
                                 IsoPos *curr_iso_pos,
                                 IsoPos *prev_iso_pos,
                                 BinarySearchTree *visited,
                                 int dbgLevel);

    void addBus(Bus *_bus);

    int nrRows() { return hMatrix->rows; }
    int nrCols() { return hMatrix->cols; }
    void dump(std::string indent);




    // Variables

    HurkaMatrix *hMatrix;           // The roadnetwork datastructure
    IsoRect *rect;                  // The rectangle it occupies in the IsoMatrix
    std::list<Bus *> *buslist;      // Buses on the roadnetwork





    // Static Utilities

    /// \brief Given a roadMatrix (matrix with 1s for roads, 0s else) find a random position where a road is
    /// \param roadMatrix Allocated HurkaMatrix object with set values
    /// \return A random position for a road
    // (--)
    static IsoPos *getRandomRoad_iso_pos(HurkaMatrix *roadMatrix)
    {
        std::string cn ="RoadNetwork.hpp";
        if(roadMatrix->rows > 10000 || roadMatrix->cols > 10000) {
            std::cout << "ERROR" << cn << " too big of a roadmatrix! " << roadMatrix->rows << ", " << roadMatrix->cols << "\n";
            return nullptr;
        }

        bool found = false;
        int allowedAttempts = 500;
        int currAttempt = 0;

        IsoPos *newPos = new IsoPos(0,0);

        int r;
        int c;

        while(found == false && currAttempt < allowedAttempts) {

            r = randBetween(0, roadMatrix->rows-1);
            c = randBetween(0, roadMatrix->cols-1);

            if(roadMatrix->matrix[r][c] == 1) {

                newPos->y = r;
                newPos->x = c;

                found = true;

            }

            currAttempt++;
        }

        if(found == false) {

            std::cout << "Could not find random bus position\n";
            return nullptr;
        }

        return newPos;
    }

private:

    // Internal function
    void createSlotPathFromDijkstraResult(DijkstraResult *dijkstraResult, SlotPath *slotpath, int debugLevel);

    std::string cn = "RoadNetwork.cpp";
};

#endif
