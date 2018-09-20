#include "IsoPos.hpp"

// Isometric Position
IsoPos::IsoPos(int _y, int _x)
{
    y = _y;
    x = _x;
}

IsoPos::IsoPos(int _y, int _x, int _rely, int _relx)
{
    y = _y;
    x = _x;
    rely = _rely;
    relx = _relx;
}


IsoPos *IsoPos::clone()
{
    return new IsoPos(y,x, rely, relx);
}


void IsoPos::dump(std::string ind)
{
    std::cout << ind << "(" << y << ", " << x << ")\n";
}



// (+-)
std::string IsoPos::absToString()
{
    std::string str = "(";

    str += std::to_string(y);

    str += "," ;

    str += std::to_string(x);

    str += ")";

    return str;
}





// (-+)
std::string IsoPos::relToString()
{
    std::string str = "(";

    str += std::to_string(rely);

    str += "," ;

    str += std::to_string(relx);

    str += ")";

    return str;
}






/// \brief If "other" is an exact match to "this", we return 0.
/// \return 0 on exact match, -1 if not.

int IsoPos::compare(IsoPos *other)
{


    if(other->y == this->y
       &&
       other->x == this->x
       &&
       other->rely == this->rely
       &&
       other->relx == this->relx
    )
    {
        return 0;
    }

    return -1;
}



/// \brief If "Other" has exact match with "this" on absolute_iso positioning, return 0.
/// \return 0 on match, -1 if not.
// (--)
int IsoPos::compareAbsIso(IsoPos *other)
{

    if(other->y == this->y
       &&
       other->x == this->x)
    {
        return 0;
    }

    return -1;

}

