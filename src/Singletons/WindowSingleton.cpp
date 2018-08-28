#include "WindowSingleton.hpp"

void WindowSingleton::allocateWindow()
{
    // All the settings are in Constants.hpp

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    rwPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, desktop.bitsPerPixel), "HurkaLumo editor 0.1-alpha");

}


void WindowSingleton::drawAll(sf::RenderTarget &rt)
{

    // Make a simple rectangle around the size of the window for debugging/developing purposes




    sf::RectangleShape rect( sf::Vector2f(rwPtr->getSize().x-2, rwPtr->getSize().y-4));


    rect.setPosition(sf::Vector2f(1,1));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,52,52,255)); // Red
    rect.setFillColor(sf::Color(0,0,0,0));// Transparent
    rt.draw(rect);
}

sf::RenderWindow *WindowSingleton::getRwPtr()
{
    return rwPtr;
}
