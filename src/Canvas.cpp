#include "Canvas.hpp"





Canvas::Canvas()
{
    // Set a default view at the topleft corner of the canvas
    hview = new HView(
            sf::Vector2f( WINDOW_WIDTH_CENTER_PX, WINDOW_HEIGHT_CENTER_PX ),
            sf::Vector2f( WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX ) );

}


HView *Canvas::getHView()
{
    return hview;
}


// (--)
void Canvas::drawAll(sf::RenderTarget& rt)
{



    int canvasXOffset = 4;
    int canvasYOffset = 4;

    // Draw rough grid lines of the Canvas

    int gridSpacingPx = 64;


    for(int y = 0; y < WINDOW_HEIGHT_PX; y+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH_PX, 1));
        line.setPosition(0 + canvasXOffset,y +canvasYOffset);
        line.setFillColor(sf::Color(0,0,120,255));
        rt.draw(line);
    }


    for(int x = 0; x < WINDOW_WIDTH_PX; x+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(1, WINDOW_HEIGHT_PX));
        line.setPosition(x + canvasXOffset,0 + canvasYOffset );
        line.setFillColor(sf::Color(0,0,120,255));
        rt.draw(line);

    }






}
