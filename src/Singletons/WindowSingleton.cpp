#include "WindowSingleton.hpp"

#include "HView.hpp"
#include "HConfig.hpp"



void WindowSingleton::allocateWindow()
{
    // Settings are in "constants.hpp" or in the HConfig singleton
    HConfig *cfg;
    cfg = cfg->getInstance();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    rwPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, desktop.bitsPerPixel), "HurkaLumo editor 0.1-alpha");


}


sf::RenderWindow *WindowSingleton::getRwPtr()
{
    return rwPtr;
}
