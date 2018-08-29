#include "Canvas.hpp"


#include "Singletons/WindowSingleton.hpp"


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



// The canvas is where we draw the gameboard on
// The canvas has a grid that you can enable to make it easier for development
// (--)
void Canvas::drawAll(sf::RenderTarget& rt)
{


    WindowSingleton *win;
    win = win->getInstance();


    int canvasXOffset = 4;
    int canvasYOffset = 4;

    // Draw Blue grid lines of the Canvas

    int gridSpacingPx = ORMATRIX_TILE_HEIGHT_PX ;

    int windowHeightPx = win->getRwPtr()->getSize().y;
    int windowWidthPx = win->getRwPtr()->getSize().x;


    // The lines are actually very thin squares

    for(int y = 0; y < windowHeightPx; y+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(windowWidthPx, 1));
        line.setPosition(0 + canvasXOffset,y +canvasYOffset);
        line.setFillColor(sf::Color(0,0,120,255));
        rt.draw(line);
    }


    for(int x = 0; x < windowWidthPx; x+= gridSpacingPx)
    {
        sf::RectangleShape line(sf::Vector2f(1, windowHeightPx));
        line.setPosition(x + canvasXOffset,0 + canvasYOffset );
        line.setFillColor(sf::Color(0,0,120,255));
        rt.draw(line);

    }






}
