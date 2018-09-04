#ifndef RENDERTREE_H
#define RENDERTREE_H

#include <vector>
#include <SFML/Graphics.hpp>

// Put stuff in the tree that you want to end up drawn on screen in the Render section in Core()

class RenderTree
{
public:
RenderTree();

void addGuiLabel( sf::Text *, void *position);
void addMiscText( sf::Text *);
void addRect( sf::RectangleShape *);

void clearAll();
void clearMiscTexts();
void clearRects();



    std::vector<sf::Text *> miscTexts;
    std::vector<sf::Text *> guiLabels;
    std::vector<sf::RectangleShape *> rects;


private:
    std::string cn = "RenderTree.cpp";
};







#endif
