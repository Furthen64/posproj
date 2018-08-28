#ifndef RENDERTREE_H
#define RENDERTREE_H

#include <vector>
#include <SFML/Graphics.hpp>

// Put stuff in the tree that you want to end up in the Render section in Core()

class RenderTree
{
public:
    RenderTree();

    void addGuiLabel( sf::Text *, void *position);
    void addMiscText( sf::Text *);

    void clearAll();
    void clearMiscTexts();



    std::vector<sf::Text *> miscTexts;
    std::vector<sf::Text *> guiLabels;


private:
};







#endif
