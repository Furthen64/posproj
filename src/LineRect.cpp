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


CanvasPos *LineRect::getTopLeft()
{
    return new CanvasPos(getTop_cpos()->y, getLeft_cpos()->x);
}


float LineRect::getSize_y()
{
    return (getBottom_cpos()->y - getTop_cpos()->y);
}

float LineRect::getSize_x()
{
    return (getRight_cpos()->x - getLeft_cpos()->x);
}


void LineRect::scale_y(float scaleFactor)
{
    // Squash! setSize is Scale really

    A->y *= scaleFactor;
    B->y *= scaleFactor;
    C->y *= scaleFactor;
    D->y *= scaleFactor;

    recalcBoundingBox();
}
void LineRect::scale_x(float size_x)
{
    //bottomRight->x = topLeft->x + size_x;
    std::cout << "STUB scale_x\n";

    recalcBoundingBox();
}


// (-+)
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


// (-+)
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
    float xDiff = newTopLeft->x - oldTopLeft->x;
    float yDiff = newTopLeft->y - oldTopLeft->y;

    A->y += yDiff;  A->x += xDiff;
    B->y += yDiff;  B->x += xDiff;
    C->y += yDiff;  C->x += xDiff;
    D->y += yDiff;  D->x += xDiff;

    recalcBoundingBox();
}


// Seems to work?
void LineRect::moveByMiddle(CanvasPos *to_cpos)
{

    bool positive_x = false;
    bool positive_y = false;

     if(boundingBox == nullptr) {
        logErr(cn + "setTopLeft boundingbox is nullptr\n");
        return ;
    }

    if(boundingBox->topLeft == nullptr) {
        logErr(cn + "setTopLeft boundingbox->topLeft is nullptr\n");
        return ;
    }


    CanvasPos *middle_cpos = getMiddle_cpos();



    // Diff between the two
    float xDiff = 0.0f;
    float yDiff = 0.0f;

    if(to_cpos->x > middle_cpos->x) {
        xDiff = to_cpos->x - middle_cpos->x;
        positive_x = true;
    } else {
        xDiff = middle_cpos->x - to_cpos->x;
        positive_x = false;
    }



    if(to_cpos->y > middle_cpos->y) {
        yDiff = to_cpos->y - middle_cpos->y;
        positive_y = true;
    } else {
        yDiff = middle_cpos->y - to_cpos->y;
        positive_y = false;

    }

    // Hm... Shouldnt it be -= or += depending on where we are in the carteisian plane?

    if(positive_x) {
        A->x += xDiff;
        B->x += xDiff;
        C->x += xDiff;
        D->x += xDiff;

    } else {
        A->x -= xDiff;
        B->x -= xDiff;
        C->x -= xDiff;
        D->x -= xDiff;

    }


    if(positive_y) {
        A->y += yDiff;
        B->y += yDiff;
        C->y += yDiff;
        D->y += yDiff;
    } else {
        A->y -= yDiff;
        B->y -= yDiff;
        C->y -= yDiff;
        D->y -= yDiff;
    }
    /*
    A->y -= yDiff;  A->x -= xDiff;
    B->y -= yDiff;  B->x -= xDiff;
    C->y -= yDiff;  C->x -= xDiff;
    D->y -= yDiff;  D->x -= xDiff;
    */
    recalcBoundingBox();

}




void LineRect::rotateAllPointsNDegCCW(float n)
{
    A->rotateAroundOrigoNDegCCW(n);
    B->rotateAroundOrigoNDegCCW(n);
    C->rotateAroundOrigoNDegCCW(n);
    D->rotateAroundOrigoNDegCCW(n);

    recalcBoundingBox();
}



void LineRect::rotateAllPointsNDegCW(float n)
{
    A->rotateAroundOrigoNDegCW(n);
    B->rotateAroundOrigoNDegCW(n);
    C->rotateAroundOrigoNDegCW(n);
    D->rotateAroundOrigoNDegCW(n);

    recalcBoundingBox();

}

/// \brief Only works with simple rectangles! No skewed weirdness, or maybe that works too, havent tried ^^

// used by "moveByMiddle()"
CanvasPos *LineRect::getMiddle_cpos()
{
    // Just get the middle of the bounding box
    return boundingBox->getMiddle_cpos();
}














