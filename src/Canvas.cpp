#include "Canvas.hpp"



Canvas::Canvas()
{

}




// (--)
void Canvas::drawAll(sf::RenderTarget& rt)
{

    // Draw rough grid lines


    int gridSpacingPx = 64;

    // How many grid lines do we want on the each axis?
    int nrGridLinesVertical = WINDOW_HEIGHT_PX / gridSpacingPx;
    int nrGridLinesHorizontal = WINDOW_WIDTH_PX / gridSpacingPx;

    for(int y = 0; y < WINDOW_HEIGHT_PX; y+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH_PX, 1));
        line.setPosition(0,y);
        line.setFillColor(sf::Color(120,120,120,255));
        rt.draw(line);
    }


    for(int x = 0; x < WINDOW_WIDTH_PX; x+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(1, WINDOW_HEIGHT_PX));
        line.setPosition(x,0);
        line.setFillColor(sf::Color(120,120,120,255));
        rt.draw(line);

    }


}
