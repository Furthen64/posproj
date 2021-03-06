#include "TrafficManager.hpp"



// (++)
TrafficManager::TrafficManager()
{
    roadNetworks = new std::list<RoadNetwork *>();
}



// (--) used by Core in clearResources
void TrafficManager::clearResources()
{

    RoadNetwork *currRoadnet;


    for(std::list<RoadNetwork *>::iterator roadsIter=roadNetworks->begin(); roadsIter != roadNetworks->end(); ++roadsIter)
    {
        currRoadnet = (*roadsIter);

        currRoadnet->clearResources();

        delete currRoadnet;
    }

}

// (+-)
void TrafficManager::drawBuses(sf::RenderWindow &rt)
{
    RoadNetwork *currRoadnet = nullptr;

    for(std::list<RoadNetwork *>::iterator roadsIter=roadNetworks->begin(); roadsIter != roadNetworks->end(); ++roadsIter)
    {
        currRoadnet = (*roadsIter);

        for(std::list<Bus *>::iterator busIter=currRoadnet->buslist->begin(); busIter != currRoadnet->buslist->end(); ++busIter)
        {
            (*busIter)->draw(rt, true);
        }
    }

}


















/// Follows connected 1:s in the fullRoadMatrix and puts 1:s in newMatrix
///
/// \param fullRoadMatrix      allocated HurkaMatrix, A matrix with 1:s where the road sprites are, 0:s everywhere else
/// \param newMatrix           allocated HurkaMatrix, empty on entry, same size as fullRoadMatrix. Populated with values when function returns.
/// \param curr_iso_pos        The current absolute iso_pos for the algorithm
/// \param min_iso_pos         Already existing hpos object, will be filled on output.
/// \param visited             BinarySearchTree already allocated, empty on entry. Will be filled when function returns.
///
/// (-+) Worked once

// Might be buggy, look at CR5 bug we had... um and look at the function createSlotpath
// RECURSIVE
void TrafficManager::follow(HurkaMatrix *fullRoadMatrix,
                            HurkaMatrix *newMatrix,
                            IsoPos *curr_iso_pos,
                            IsoPos *min_iso_pos,
                            IsoPos *max_iso_pos,
                            BinarySearchTree *visited,
                            int debugLevel)
{
    std::string ind = "      ";

    if(debugLevel >= 2) {
        std::cout << ind << "follow()    currpos=";
        curr_iso_pos->dump(ind);
    }

    if(debugLevel >= 2) {
        std::cout <<  "\n";
    }




    /// Have we been here?
    int searchId = Node::genIDfrom_abs_iso(curr_iso_pos);
    if(visited->findVal(searchId,0) != -1 ) {
        return ;                                                                                 // END RECURSION
    }



    /// Setup objects


    IsoPos  *up_iso = curr_iso_pos->clone();      // SPEEDUP could probably do without cloning and stuff and allocating all these HPos's
    up_iso->y -= 1;

    IsoPos *right_iso = curr_iso_pos->clone();
    right_iso->x += 1;

    IsoPos *down_iso = curr_iso_pos->clone();
    down_iso->y += 1;

    IsoPos *left_iso = curr_iso_pos->clone();
    left_iso->x -= 1;



    /// Update objects

    // Put a "1" where we are at the moment
    newMatrix->matrix[(int)curr_iso_pos->y][(int)curr_iso_pos->x] = 1;

    // Add to visited
    visited->add(searchId,debugLevel);


    // Update the limits
    if(min_iso_pos->y > curr_iso_pos->y) {
        // new minimum! Top road
        min_iso_pos->y = curr_iso_pos->y;
    }

    if(min_iso_pos->x > curr_iso_pos->x) {
        // new minimum! left road
        min_iso_pos->x = curr_iso_pos->x;

    }


    if(max_iso_pos->x < curr_iso_pos->x) {
        // new max! right road
        max_iso_pos->x = curr_iso_pos->x;
    }

    if(max_iso_pos->y < curr_iso_pos->y) {
        // new max! down road
        max_iso_pos->y = curr_iso_pos->y;
    }









    /// Go up
    if(up_iso->y >= 0) { // Not hit the wall yet?
        if(fullRoadMatrix->matrix[(int)up_iso->y][(int)up_iso->x] == 1) { // is it a road?
            if(debugLevel >= 2) { std::cout << ind << "going up\n"; }
            follow(fullRoadMatrix, newMatrix, up_iso, min_iso_pos, max_iso_pos, visited, debugLevel);                                 // RECURSION CALL
        }
    }


    /// Go right
    if(right_iso->x <= (fullRoadMatrix->cols-1)) {
        if(fullRoadMatrix->matrix[(int)right_iso->y][(int)right_iso->x] == 1) {
            if(debugLevel >= 2) { std::cout << ind << "going right\n";}
            follow(fullRoadMatrix, newMatrix, right_iso, min_iso_pos, max_iso_pos, visited, debugLevel);                              // RECURSION CALL
        }
    }


    /// Go down
    if(down_iso->y <= (fullRoadMatrix->rows-1)) {
        if(fullRoadMatrix->matrix[(int)down_iso->y][(int)down_iso->x] == 1) {
            if(debugLevel >= 2) { std::cout << ind  << "going down\n"; }
            follow(fullRoadMatrix, newMatrix, down_iso, min_iso_pos, max_iso_pos, visited, debugLevel);                               // RECURSION CALL
        }
    }



    /// Go left
    if(left_iso->x >= 0) {
        if(fullRoadMatrix->matrix[(int)left_iso->y][(int)left_iso->x] == 1) {
            if(debugLevel >= 2) { std::cout << ind  << "going left\n"; }
            follow(fullRoadMatrix, newMatrix, left_iso, min_iso_pos, max_iso_pos, visited, debugLevel);                               // RECURSION CALL
        }
    }


                                                                                                // END RECURSION
}














//
// wishlist: Makeover! Minimilize by using a RoadNetwork *pointer instead of the individual parts  (newMatrix, min_iso, max_iso...)

/// \brief Creates a RoadNetwork, calls recursive function that walks through the matrix, following the 1:s
/// \param fullRoadMatrix  A matrix with all the roads as 1:s, anything else as 0:s
/// \param curr_iso_pos    The position of which to start following the 1:s
/// \param min_iso_pos     Min y and x limits
/// \param max_iso_pos     Max y and x limits
/// \param visited         used internally, just supply an allocated BinarySearchTree


// alpha-0.2: FIXME test more please pretty please!
// (-+)
RoadNetwork *TrafficManager::followMatrixAndAddRoadsToBST(HurkaMatrix *fullRoadMatrix,
                                                           IsoPos *curr_iso_pos,
                                                           IsoPos *min_iso_pos,
                                                           IsoPos *max_iso_pos,
                                                           BinarySearchTree *visited,
                                                           int debugLevel)
{
    std::string ind = "   ";

    if(debugLevel >= 1)  {
        std::cout << ind << "\n\nfollowAndAddToBST():\n";
    }



    // Create an empty matrix for the RoadNetwork

    HurkaMatrix *hmatrix = new HurkaMatrix(fullRoadMatrix->rows, fullRoadMatrix->cols);



    /// Follow the roads in the original matrix (the 1:s)
    /// When it's done, "hmatrix" should contain the roadnetwork's matrix

    if(debugLevel >= 2)  {
        std::cout << ind << "\nfollow():\n" << ind << "{\n";
    }

    follow(fullRoadMatrix, hmatrix, curr_iso_pos, min_iso_pos, max_iso_pos, visited, debugLevel);



    if(debugLevel >= 2)  {
        std::cout << ind << "}\n\n";
    }



    // Setup the return object
    int newRows = max_iso_pos->y - min_iso_pos->y +1;  // lite os�ker, +-1 felet
    int newCols = max_iso_pos->x - min_iso_pos->x +1;



    // We only want a matrix with the size containing roads, not the whitespace around it

    if(debugLevel >= 2)  {
        std::cout << "hmatrix now:\n";
        hmatrix->dump();
    }


    ///         int **copySubMatrix(int **srcMtx,    int srcRows,   int srcCols,   int startY,                int startX,        int height, int width)

    hmatrix->matrix = copySubMatrix(hmatrix->matrix, hmatrix->rows, hmatrix->cols, min_iso_pos->y, min_iso_pos->x, newRows,   newCols, 0);
    if(hmatrix->matrix == nullptr) {
        std::cout << "ERROR " << cn << " Something went wrong while copying a subsection of a matrix to another matrix!\n";
        return nullptr;
    }
    hmatrix->rows = newRows;
    hmatrix->cols = newCols;

    if(debugLevel >= 2)  {
        std::cout << "New matrix after sub:\n";
        hmatrix->dump();
    }





    RoadNetwork *roadNetwork = new RoadNetwork();
    roadNetwork->hMatrix = hmatrix;
    roadNetwork->rect = new IsoRect(curr_iso_pos->clone(),
                                  newRows,
                                  newCols,
                                  GRID_TEXTURE_HEIGHT,
                                  GRID_TEXTURE_WIDTH);

    if(debugLevel >= 1)  {
        std::cout << ind << "Completed a roadnetwork:\n";
        roadNetwork->dump(ind);
    }




    return roadNetwork;
}







/// \brief Follow the 1:s in the roadmatrix, and group together them into RoadNetworks
/// \brief After its done, it should have populated the std::list<RoadNetwork *> *roadNetworks in TrafficManager
/// \return 0 on ok, -1 on failure
// (--)
int TrafficManager::readRoadNetworksFromHMatrix(HurkaMatrix *roadMatrix, int debugLevel)
{

    if(debugLevel >= 1) {
        std::cout << "\n\nparseCurrentRoads()\n----------------------------------\n";
    }

    BinarySearchTree *bst = new BinarySearchTree();
    IsoPos *min_iso_pos = new IsoPos (0,0);
    IsoPos  *max_iso_pos = new IsoPos (0,0);

    int searchId = -1;

    int M_LENGTH = roadMatrix->rows;
    int N_LENGTH = roadMatrix->cols;


    // Debug Control!
    int maxLogs = 50;
    int nrLogs = 0;


    if(debugLevel >=2) {
        roadMatrix->dump();
    }


    if(debugLevel >=2) {
        bst->dump();
    }

    IsoPos *curr_iso = new IsoPos();



    /// Start your engines!
    /// Walk the Matrix

    // Reset the variables for each roadNetwork:
    min_iso_pos->y = roadMatrix->rows;
    min_iso_pos->x = roadMatrix->cols;

    max_iso_pos->y = 0;
    max_iso_pos->x = 0;




    if(debugLevel >=1) {std::cout << "\n\nIterating all the cells:\n-------------------\n";}

    for(int y = 0; y < M_LENGTH; y++) {
        for(int x = 0; x < N_LENGTH; x++) {


            curr_iso->y = y;
            curr_iso->x = x;

            searchId = Node::genIDfrom_abs_iso(curr_iso);

            if(debugLevel >=1 && nrLogs < maxLogs) {std::cout << "Pos(" << y << ", " << x << ") id=" << searchId << "\n";}

            if(roadMatrix->matrix[y][x] == 1) {

                // Search in bst

                if(bst->findVal(searchId,0) != -1) {

                    // found it!    Ignore it. We found it so it's already been visited.

                    if(debugLevel >=1 && nrLogs < maxLogs) {std::cout << "Already in BST\n";}



                } else {


                    if(debugLevel >=1) {std::cout << "Running followAndAddToBst which generates a RoadNetwork\n";}

                    // Did not find it?
                    // Start a "Follow and Add" recursion, which returns a roadNetwork


                    RoadNetwork *network = followMatrixAndAddRoadsToBST(roadMatrix, curr_iso, min_iso_pos, max_iso_pos, bst, debugLevel);

                    if(network == nullptr) {
                        std::cout << "ERROR " << cn << " parseCurrentRoads() failed while executing: followAndAddToBST(), got nullptr.\n";
                        std::cout << "Given roadmatrix:\n";
                        roadMatrix->dump();

                        return -1;
                    }


                    // Store a completed roadnetwork
                    roadNetworks->push_back(network);


                    // Reset for the next round
                    min_iso_pos->y = roadMatrix->rows;
                    min_iso_pos->x = roadMatrix->cols;

                    max_iso_pos->y = 0;
                    max_iso_pos->x = 0;

                }


            } // if value == 1 in matrix



            // Do the next cell in matrix
            nrLogs++;
        }
    }

    return 0;

}






/// \brief Look and see if there is a roadnetwork at this "searchpos".
/// \brief Go over all RoadNetworks and all their positions to see if any of them match the HPos searchpos.
// Speed: O(N^2) at worst
// (--) bug with relative positioning... keep saying invalid searchposition     2018-06-15
//      testing CR#19
RoadNetwork *TrafficManager::roadNetworkAtPos(IsoPos  *searchpos)
{
    int debugLevel = 0;
    bool foundRoad = false;


    if(searchpos==nullptr) {
        std::cout << "ERROR " << cn << " roadNetworkAtPos got nullptr\n";
        return nullptr;
    }



    IsoPos  *relpos = new IsoPos (searchpos->y, searchpos->x);


    for (std::list<RoadNetwork *>::iterator it=roadNetworks->begin(); it != roadNetworks->end(); ++it) {

        RoadNetwork *currNet = (*it);



        // Are we not inside the bounds of this roadnetwork?
        if(!currNet->rect->containsIsoPos(searchpos)) {
            continue; // Take the next one, not worth looking in to this network.
        }


        //  deleteme:
        //        if((searchpos->y < currNet->min_isoYOffset)
        //||
        //(searchpos->x < currNet->min_isoXOffset))  {
        //
        //continue; // Take the next one, not worth looking in to this network.
        //
        //}





        // Transform the absolute values from the searchpos into relative position for current roadnetwork

        relpos->rely = relpos->y - currNet->rect->absStart->y;
        relpos->relx = relpos->x - currNet->rect->absStart->x;

        // relpos->relx = relpos->x - currNet->min_isoXOffset; deleteme



        if(relpos->rely < 0 || relpos->relx < 0) {
            std::cout << "Invalid searchposition: relpos(" << relpos->rely << ", " << relpos->relx << ") \n";
            continue;
        }

        if(currNet->hMatrix == nullptr) {
            std::cout << "This roadnetwork has no hmatrix\n";
            continue;
        }

        foundRoad = currNet->hMatrix->roadAtRelPos(relpos, debugLevel-1);


        if(foundRoad) {
            if(debugLevel >=1) {
                std::cout << "Found the roadnetwork for position " << searchpos->absToString() << "!\n";
            }
            return currNet;
        }



    }

    return nullptr;


}





///
/// High level functions
///
// Tested, works
// (-+)
void TrafficManager::dumpRoadNetworks(std::string indent, bool header)
{

    if(header) {
        std::cout << indent << "\n\nTrafficManager's current Road Networks:\n------------------------------------\n";
    }

    int nr = 0;





    for (std::list<RoadNetwork *>::iterator it=roadNetworks->begin(); it != roadNetworks->end(); ++it) {

        RoadNetwork *currNet = (*it);

        currNet->dump(indent);

        nr++;
    }

}

/// \brief updates all the buses on all the roadnetworks with their gameUpdate() function
/// \param viewHPos Current viewing position
/// (--)
void TrafficManager::updateAll()
{

    int dbgLevel = 0;

    RoadNetwork *currRoadnet = nullptr;
    Bus *currBus = nullptr;

    int roadnr = 0;
    int busnr = 0;

    for(std::list<RoadNetwork *>::iterator roadsIter=roadNetworks->begin(); roadsIter != roadNetworks->end(); ++roadsIter)
    {

        currRoadnet = (*roadsIter);

        for(std::list<Bus *>::iterator busIter=currRoadnet->buslist->begin(); busIter != currRoadnet->buslist->end(); ++busIter)
        {
            if(dbgLevel>=1) { std::cout << "roadnet=" << roadnr << " is updating bus nr=" << busnr << "\n";  }

            currBus = (*busIter);

            // Find out which network it is on
            currBus->gameUpdate(currRoadnet);

            busnr++;
        }

        roadnr++;
        busnr=0;
    }



}






///
/// Individual
///


void addRoadNetwork()
{
}


// (--) Make
DijkstraResult *TrafficManager::runDijkstraOnBus(int busId, Vector2f *from_iso_pos, Vector2f *to_iso_pos)
{
    std::cout << "NOT CODED YET             Given a busid , find the bus in the buslist and run dijkstra on A->B, \n";
    return nullptr;
}





// Testing alpha-0.1:
//          (2018-05-13) "dijkstra_test_1.txt"                     Works!
//          (2018-05-13) "dijkstra_test_2.txt"                     Works!
//          (2018-05-15) "dijkstra_test_3.txt"                     Works!
//          (2018-05-15) "dijkstra_test_4.txt"                     Works!
//          (2018-05-15) "dijkstra_test_5.txt"                     Works!






/// \brief Makes plans for how all the buses should move by iterating the roadNetworks datastructures and finding all the buses.
/// \param debugLevel selfexplanatory
/// \param fromRoad nr road in the map
/// \param toRoad  nr road in the map
/// \return 0 on OK , -1 on failure
// (--+)
int TrafficManager::planForBusesOnRoadNetwork(int debugLevel, int fromRoad, int toRoad, bool dijkstraAutoEndpointsAdjust)
{


    std::string ind = "  ";
    RoadNetwork *roadnet = nullptr;
    Bus *bus = nullptr;
    SlotPath *slotpath;
    IsoPos *abs_iso_pos_A = nullptr;
    IsoPos *abs_iso_pos_B  = nullptr;

    IsoPos *rel_iso_pos_A = nullptr;
    IsoPos *rel_iso_pos_B  = nullptr;

    int autoboundNr = 0;
    int autoboundAllowed = 400;
    int attemptRoadNr = 9999;

    if(debugLevel >=1) { std::cout << "planForBusesOnRoadNetwork....\n"; }




    /// Error check

    if(roadNetworks->size() <= 0) {
        std::cout << "note: " << cn << " there are no roadnetworks to work with.\n";
        return 0;
    }



    /// Loop all the RoadNetworks

    for(std::list<RoadNetwork *>::iterator itRn = roadNetworks->begin(); itRn != roadNetworks->end(); ++itRn)
    {
        roadnet = (*itRn);

        if(roadnet == nullptr) {
            std::cout << "ERROR " << cn << " roadnet is null in planForBusesOnRoadNetwork when iterating roadNetworks\n";
            return -1;
        }



        /// Loop all the RoadNetwork's Buses

        for(std::list<Bus *>::iterator itBus = roadnet->buslist->begin(); itBus != roadnet->buslist->end(); ++itBus)
        {


            bus = (*itBus);

            if(bus == nullptr) {
                std::cout << "ERROR " << cn << " one of the buses in the roadnet's buslist is nullptr.\n";
                return -1;
            }





            /// Set A to B positions

            // Wishlist: Needs something sensible to go on for start and end position ...
            // Like a Bus Station

            abs_iso_pos_A  = roadnet->getNrRoad_iso(fromRoad, debugLevel-1);

            if(abs_iso_pos_A == nullptr) {
                std::cout << "ERROR " << cn << " could not set start position\n";
                return -1;
            }







            // For now we have the flag "dijkstraAutoEndpointsAdjust"!
            autoboundNr = 0;    // vs autoboundAllowed


            attemptRoadNr = toRoad;

            if(dijkstraAutoEndpointsAdjust) {

                // Try the "toRoad" nr and if that dont work, step back once and try again, until we find a road

                while(autoboundNr < autoboundAllowed)
                {


                    abs_iso_pos_B  = roadnet->getNrRoad_iso(attemptRoadNr, debugLevel -1);

                    if(abs_iso_pos_B != nullptr) {
                        break;
                    }



                    autoboundNr++;
                    attemptRoadNr--;        // Pull back and see if that helps

                }
            } else {


                // Just use whatever "toRoad" is set to
                abs_iso_pos_B  = roadnet->getNrRoad_iso(toRoad, debugLevel);

                if(abs_iso_pos_B == nullptr) {
                    std::cout << "ERROR " << cn << " could not set end position\n";
                    return -1;
                }
            }





            rel_iso_pos_A = abs_iso_pos_A->clone();
            rel_iso_pos_B = abs_iso_pos_B->clone();

            /// For now, make sure we have _no_ absolute positions when entering createSlotPath() (2018-05)
            // remove it later on

            rel_iso_pos_A->y = 0;
            rel_iso_pos_A->x = 0;

            rel_iso_pos_B->y = 0;
            rel_iso_pos_B->x = 0;




            /// Run Dijkstra to generate the path
            slotpath = roadnet->createSlotPath(rel_iso_pos_A, rel_iso_pos_B, debugLevel);

            bus->setSlotPath(slotpath);



        }
    }

    if(debugLevel >=1) { std::cout << "                                complete.\n"; }




    return 0;
}

void TrafficManager::updateBusesOnRoadNetwork(int busId, int roadnetId) {
     std::cout << "NOT CODED YET            Update all the buses on a given roadnet? not sure I need this... hm..\n";
}



int TrafficManager::nrOfRoadnetworks()
{
    return roadNetworks->size();
}

/// \brief adds a bus to the roadnetwork you search for
/// \param _bus Allocated bus
/// \param _roadnetId Find nr "roadnetId" of all the roadnets, good enough for alpha-0.1
/// Wishlist: better finding of a particular roadnetwork
/// (--)
void TrafficManager::addBus(Bus *_bus, int roadnetId)
{

    int debugLevel = 0;

    // iterate over the roadnets and find a roadnet
    RoadNetwork *currNet = nullptr;

    int nr = 0;


    if(debugLevel >=1) { std::cout << "** addBus() {\n"; }

    // Find the RoadNetwork
    for( std::list<RoadNetwork *>::iterator it=roadNetworks->begin(); it != roadNetworks->end(); ++it)
    {
        if(debugLevel >=1) {std::cout << "nr=" << nr << "\n";}
        currNet = (*it);

        if(roadnetId == nr) {
            if(debugLevel >=1) {std::cout << "adding bus to roadnet=" << nr<<"\n";}
            break;
        }


        nr++;

    }

    if(currNet == nullptr) {
        std::cout << "ERROR " << cn << " We got no roads...\n";
        return ;
    }



    /// Finally add it to the right roadnet
    currNet->addBus(_bus);

    if(debugLevel >=1) {std::cout << "}\n"; }
}





























