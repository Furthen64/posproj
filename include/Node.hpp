#ifndef NODE_H
#define NODE_H


#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <climits>
#include <sstream>


#include "IsoPos.hpp"


class Link; // Forward declaration

enum NODE_DIR {
    dir_up,
    dir_right,
    dir_down,
    dir_left
};






// A very HEAVY class
// Its use with the Dijkstra algorithm makes it so that we need to overload the "<" operator
// in order to put it in a prio queue
//
// It also has some member labels for the algorithm to work (labels)
//
// It also contains HPos for positioning in the gamematrix


class Node
{
public:
    Node(std::string _name, int _id, IsoPos *_rel_iso_pos);


    void createLink();
    void dump(int indent);
    int getId();
    std::string getName();

    Node *attachNodeUp(Node *other);
    Node *attachNodeRight(Node *other);
    Node *attachNodeDown(Node *other);
    Node *attachNodeLeft(Node *other);

    Node *attachNewNode(std::string , int , IsoPos *, int , int , int );

    void resetForDijkstra();
    int connectNodes(Node *firstNode, Node *secondNode, int relDir, int weight1, int weight2, int debugLevel);




    int textureId;

    IsoPos *get_rel_iso_pos();
    IsoPos *get_copy_rel_iso_pos();



    /// Variables
    Link *up;
    int upLabel = INT_MAX;
    Link *right;
    int rightLabel = INT_MAX;
    Link *down;
    int downLabel = INT_MAX;
    Link *left;
    int leftLabel = INT_MAX;

    /// Dijkstra stuff on top of the graph
    Node *fastestPrevNode = nullptr;
    int permanentLabel = INT_MAX;
    int tempLabel = INT_MAX;



    // How should it handle id:s under 10000? where M=0?        // 2018-03-20
    // (--)
    /// \brief Converts the supplied y and x values back to their respective iso positions
    /// \param _id "Graph Searchid". For example: 10006, will become y=1, x=6
    /// \param y
    /// \param x
    static void idTo_iso_pos(int graphSearchId, int *y, int *x)
    {
        //if(graphSearchId > 10000) {
            (*y) = graphSearchId/10000;
            (*x) = graphSearchId-(10000* (*y));
        //}

    }





    // ?? used by what? and hpos contains what values?
    static int genIDfrom_rel_iso(IsoPos *_hpos)
    {

        if(_hpos->rely < 0) {
            std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
            return -1;
        }

        if(_hpos->relx < 0) {
            std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
            return -1;
        }

        return _hpos->rely * 10000 + _hpos->relx;
    }




    // used by indexInBlockList
    static int genIDfrom_abs_iso(IsoPos *_hpos)
    {
        if(_hpos->y < 0) {
            std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
            return -1;
        }

        if(_hpos->x < 0) {
            std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
            return -1;
        }

        return _hpos->y * 10000 + _hpos->x;
    }




    // (++) alpha-0.1
    static std::string rel_iso_to_str(IsoPos *hpos)
    {

        std::stringstream sstm;

        sstm << "(" << hpos->rely << "," << hpos->relx << ")";

        return sstm.str();
    }


    // (++) alpha-0.1
    static std::string abs_iso_to_str(IsoPos *hpos)
    {
        std::stringstream sstm;

        sstm << "(" << hpos->y << "," << hpos->x << ")";

        return sstm.str();
    }





private:
    std::string name;
    int id;
    IsoPos *rel_iso_pos;
    std::string cn = "Node.cpp";
};


#endif
