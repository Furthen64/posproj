#ifndef ISOPOS_H
#define ISOPOS_H


#include <iostream>
#include <string>


class IsoPos
{
public:
    IsoPos() {}
    IsoPos(int, int);
    IsoPos(int , int , int , int );

    IsoPos *clone();
    void dump(std::string ind);

    std::string absToString();
    std::string relToString();

    int compare(IsoPos *other);
    int compareAbsIso(IsoPos *other);


    static bool ArightOfB(IsoPos *A, IsoPos *B)
    {

        if(A->x > B->x) {
            return true;
        }

        return false;
    }



    // (-+)
    static int compareTwoAbsIso(IsoPos *A, IsoPos *B)
    {

        if(A->y == B->y
           &&
           A->x == B->x)
        {
            return 0;
        }

        return -1;
    }




    int y;
    int x;
    int rely;
    int relx;

private:
    std::string cn = "IsoPos.cpp";
};

#endif
