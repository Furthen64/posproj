#include "HView.hpp"

#include <math.h>
#include "Singletons/WindowSingleton.hpp"


HView::HView()
{
}

HView::HView(sf::Vector2f _sfCenterPos, sf::Vector2f _sfSize)
{
    sfView = new sf::View(_sfCenterPos,_sfSize);


    // Figure out the topLeft position on the Canvas
    int canvasYPos = _sfCenterPos.y - (_sfSize.y/2);
    int canvasXPos = _sfCenterPos.x - (_sfSize.x/2);

    topLeft = new CanvasPos(canvasYPos, canvasXPos);
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



    /// Wishlist: deal with the sfView moving around :>
    /// /!\ Dont forget to update topLeft




    // Assign this view to the current window to make the update
    rwPtr->setView(*sfView);    // Dereference our sfView because setView takes a parameter &sf::View object)

}

CanvasPos *HView::getTopLeft()
{
    return topLeft;
}


void HView::setTopLeft(CanvasPos *ptr)
{
    topLeft = ptr;
}

void HView::drawAll(sf::RenderTarget &rt)
{
    // Draw a Green rectangle to show the View size (which always is the size of the Window)

    sf::RectangleShape rect(sf::Vector2f(sfView->getSize().x-6,sfView->getSize().y-8));
    rect.setPosition(3,3);  // Window positioning
    rect.setOutlineThickness(1.0f);

    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(72,144,82,255));

    rt.draw(rect);
}

