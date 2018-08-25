#include "WindowSingleton.hpp"

void WindowSingleton::allocateWindow()
{
    // All the settings are in Constants.hpp

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    wPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, desktop.bitsPerPixel), "HurkaLumo editor 0.1-alpha");

}


sf::RenderWindow *WindowSingleton::getWPtr()
{
    return wPtr;
}
