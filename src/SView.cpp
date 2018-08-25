#include "SView.hpp"


SView::SView()
{
    view = new sf::View();
}

void SView::resizeView(int newHeightPx, int newWidthPx)
{
    view->setSize( 1024.0f, 768.0f);
    //view->setSize(  (float)newWidthPx, (float)newHeightPx );    // FIXME varför funkar inte detta?
}
