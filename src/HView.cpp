#include "HView.hpp"

#include <math.h>
#include "Singletons/WindowSingleton.hpp"
HView::HView()
{
}






HView::HView(sf::Vector2f _sfCenterPos, sf::Vector2f _sfSize)
{
    sfView = new sf::View(_sfCenterPos,_sfSize);
}


/// \brief Resizes the sfml view to match the current size of the window
// (--)
void HView::resizeViewToWindow()
{

    WindowSingleton *win; win = win->getInstance();
    sf::RenderWindow *rwPtr = win->getRwPtr();

    // Set the sfml view size to the newly resized window size
    sfView->setSize(rwPtr->getSize().x , rwPtr->getSize().y);

    // Place the view, locked against top left corner of Canvas
    sfView->setCenter( (float)round(rwPtr->getSize().x/2),
                     (float)round(rwPtr->getSize().y/2) );



    // Assign this view to the current window to make the update
    rwPtr->setView(*sfView);    // Dereference our sfView because it takes a parameter &sf::View object)

}

void *HView::getTopLeft()
{
    return topLeft;
}


void HView::setTopLeft(void *ptr)
{
    topLeft = ptr;
}

void HView::drawAll(sf::RenderTarget &rt)
{

    sf::RectangleShape rect(sf::Vector2f(sfView->getSize().x-6,sfView->getSize().y-6));
    rect.setPosition(3,3);  // Window position
    rect.setOutlineThickness(1.0f);

    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(72,144,82,255));

    rt.draw(rect);
}

