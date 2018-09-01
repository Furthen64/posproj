#include "WindowSingleton.hpp"
#include "HConfig.hpp"

void WindowSingleton::allocateWindow()
{
    // Settings are in "constants.hpp" or in the HConfig singleton
    HConfig *cfg;
    cfg = cfg->getInstance();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    rwPtr = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, desktop.bitsPerPixel), "HurkaLumo editor 0.1-alpha");

    std::string fpsLockStr = cfg->getSetting("fpsLock");
    if(fpsLockStr != "") {
        fpsLock = std::stoi(fpsLockStr);
    }

    if(fpsLockOn) {
        rwPtr->setFramerateLimit(fpsLock);
    }

}


void WindowSingleton::drawAll(sf::RenderTarget &rt, HView *hview)
{

    // Make a simple rectangle around the size of the window for debugging/developing purposes

    sf::RectangleShape rect( sf::Vector2f(rwPtr->getSize().x-2, rwPtr->getSize().y-4));





    // sfml's "setPosition()" operates in sfml canvas space.
    // So we need to adjust with our view to always lock this to what is displayed on the Window.
    // We do this by offseting with view's topleft.

    rect.setPosition(sf::Vector2f(hview->getTopLeft_x() + 1,
                                  hview->getTopLeft_y() + 1));



    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,52,52,255)); // Red
    rect.setFillColor(sf::Color(0,0,0,0));// Transparent
    rt.draw(rect);
}

sf::RenderWindow *WindowSingleton::getRwPtr()
{
    return rwPtr;
}
