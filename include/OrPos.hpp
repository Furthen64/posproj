#ifndef ORPOS_H
#define ORPOS_H


#include <iostream>
#include <string>


class OrPos
{
public:
    OrPos();
    OrPos(float _y, float _x);

    float y;
    float x;

    void dump(std::string ind);

private:

 std::string cn = "OrPos.cpp";


};




#endif
