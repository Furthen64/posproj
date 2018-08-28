#include "RenderTree.hpp"

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
    std::cout << "NOT IMPLEMENTED\n";

}



void RenderTree::clearAll()
{
}

void RenderTree::clearMiscTexts()
{
    miscTexts.clear();
}
