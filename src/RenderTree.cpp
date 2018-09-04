#include "RenderTree.hpp"


#include "Utilities/Utils.hpp"
#include <iostream>

RenderTree::RenderTree()
{

}


void RenderTree::addMiscText( sf::Text *textPtr)
{
    miscTexts.push_back(textPtr);
}



void RenderTree::addGuiLabel( sf::Text *textPtr, void *position)
{
    logWarn(cn + " addGuiLabel() void * position\n");

    guiLabels.push_back(textPtr);

}



void RenderTree::clearAll()
{
    miscTexts.clear();
}

void RenderTree::clearMiscTexts()
{
    miscTexts.clear();
}


void RenderTree::clearRects()
{
    rects.clear();
}
