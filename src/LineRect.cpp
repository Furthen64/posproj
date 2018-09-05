#include "LineRect.hpp"

#include "Utilities/Utils.hpp"
LineRect::LineRect()
{
    A = new CanvasPos(0,0);
    B = new CanvasPos(0,10);
    C = new CanvasPos(10,10);
    D = new CanvasPos(10,0);

    recalcBoundingBox();
}


LineRect::LineRect(CanvasPos *_A, CanvasPos *_B, CanvasPos *_C, CanvasPos *_D)
{
    if(_A == nullptr) { logWarn(cn + "LineRect() A is nullptr\n"); }
    if(_B == nullptr) { logWarn(cn + "LineRect() B is nullptr\n"); }
    if(_C == nullptr) { logWarn(cn + "LineRect() C is nullptr\n"); }
    if(_D == nullptr) { logWarn(cn + "LineRect() D is nullptr\n"); }


    A = _A;
    B = _B;
    C = _C;
    D = _D;

    recalcBoundingBox();
}



void LineRect::drawAll(sf::RenderTarget &rt)
{
    if(A == nullptr || B== nullptr || C== nullptr || D==nullptr) {
        return ;
    }
    sf::Vertex lineA[2];
    sf::Vertex lineB[2];
    sf::Vertex lineC[2];
    sf::Vertex lineD[2];

    // A to B
    lineA[0].color = sf::Color(0,255,0);
    lineA[1].color = sf::Color(0,255,0);
    lineA[0].position = A->getSfVec();
    lineA[1].position = B->getSfVec();

    // B to C
    lineB[0].color = sf::Color(0,0,255);
    lineB[1].color = sf::Color(0,0,255);
    lineB[0].position = B->getSfVec();
    lineB[1].position = C->getSfVec();

    // C to D
    lineC[0].color = sf::Color(255,0,0);
    lineC[1].color = sf::Color(255,0,0);
    lineC[0].position = C->getSfVec();
    lineC[1].position = D->getSfVec();

    // D to A
    lineD[0].color = sf::Color(125,125,125);
    lineD[1].color = sf::Color(125,125,125);
    lineD[0].position = D->getSfVec();
    lineD[1].position = A->getSfVec();



    rt.draw(lineA, 2, sf::Lines);
    rt.draw(lineB, 2, sf::Lines);
    rt.draw(lineC, 2, sf::Lines);
    rt.draw(lineD, 2, sf::Lines);




    boundingBox->drawAll(rt);

}


/// \brief Find the most top point out of A,B,C and D
CanvasPos *LineRect::getTop_cpos()
{
    CanvasPos* currTop_cpos = A;
    int yMin = A->y;

    if(yMin > B->y) { yMin = B->y; currTop_cpos = B; }
    if(yMin > C->y) { yMin = C->y; currTop_cpos = C;}
    if(yMin > D->y) { yMin = D->y; currTop_cpos = D;}


    return currTop_cpos;
}

CanvasPos *LineRect::getLeft_cpos()
{
    CanvasPos* currLeft_cpos = A;
    int xMin = A->x;

    if(xMin > B->x) { xMin = B->x; currLeft_cpos = B; }
    if(xMin > C->x) { xMin = C->x; currLeft_cpos = C;}
    if(xMin > D->x) { xMin = D->x; currLeft_cpos = D;}


    return currLeft_cpos;
}

CanvasPos *LineRect::getRight_cpos()
{
    CanvasPos* currRight_cpos = A;
    int xMax = A->x;

    if(xMax < B->x) { xMax = B->x; currRight_cpos = B; }
    if(xMax < C->x) { xMax = C->x; currRight_cpos = C;}
    if(xMax < D->x) { xMax = D->x; currRight_cpos = D;}


    return currRight_cpos;
}

CanvasPos *LineRect::getBottom_cpos()
{
    CanvasPos* currBottom_cpos = A;
    int yMax = A->y;

    if(yMax < B->y) { yMax = B->y; currBottom_cpos = B; }
    if(yMax < C->y) { yMax = C->y; currBottom_cpos = C;}
    if(yMax < D->y) { yMax = D->y; currBottom_cpos = D;}


    return currBottom_cpos;
}





void LineRect::moveToOrigo()
{

    std::cout << "how do I move 4 things that could look anytwhere"
    << "to anything"
    << "bounding box first"
    <<"whiteboard plz\n";
}

void LineRect::moveBack()
{

}


float LineRect::getSize_y()
{
    return (getBottom_cpos()->y - getTop_cpos()->y);
}

float LineRect::getSize_x()
{
    return (getRight_cpos()->x - getLeft_cpos()->x);
}


void LineRect::setSize_y(float size_y)
{
    std::cout << "STUB setSize_y\n";
    //bottomRight->y = topLeft->y + size_y;

    recalcBoundingBox();
}
void LineRect::setSize_x(float size_x)
{
    //bottomRight->x = topLeft->x + size_x;
    std::cout << "STUB setSize_x\n";

    recalcBoundingBox();
}


// (--) untested
void LineRect::recalcBoundingBox()
{
    // find out the most top point (lowest y-value)
    CanvasPos *top = getTop_cpos();
    // find out the most left point .. and so on.
    CanvasPos *left = getLeft_cpos();
    CanvasPos *right = getRight_cpos();
    CanvasPos *bottom = getBottom_cpos();


    // Now make a square out of these coordinates
    CanvasPos *_topLeft = new CanvasPos( top->y, left->x);
    CanvasPos *_bottomRight = new CanvasPos( bottom->y, right->x);

    boundingBox = new HRect(_topLeft, _bottomRight);
}


// (--)
// Moves all 4 corners by recalculating their positions, also recaulcaltes the new boundingBox
void LineRect::setTopLeft(CanvasPos *_topleft)
{
    if(boundingBox == nullptr) {
        logErr(cn + "setTopLeft boundingbox is nullptr\n");
        return ;
    }

    if(boundingBox->topLeft == nullptr) {
        logErr(cn + "setTopLeft boundingbox->topLeft is nullptr\n");
        return ;
    }

    CanvasPos *oldTopLeft = boundingBox->topLeft;
    CanvasPos *newTopLeft = _topleft;

    // Diff between the two
    int xDiff = newTopLeft->x - oldTopLeft->x;
    int yDiff = newTopLeft->y - oldTopLeft->y;

    A->y += yDiff;  A->x += xDiff;
    B->y += yDiff;  B->x += xDiff;
    C->y += yDiff;  C->x += xDiff;
    D->y += yDiff;  D->x += xDiff;

    recalcBoundingBox();
}




void LineRect::rotateAllPointsNDegCCW(float n)
{

    A->rotateAroundOrigoNDegCCW(n);
    B->rotateAroundOrigoNDegCCW(n);
    C->rotateAroundOrigoNDegCCW(n);
    D->rotateAroundOrigoNDegCCW(n);

}
















