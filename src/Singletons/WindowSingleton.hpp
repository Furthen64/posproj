#ifndef WINDOWSINGLETON_H
#define WINDOWSINGLETON_H


#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "HView.hpp"



/// Example usage:
///  Create a handle wherever:
///     WindowSingleton *win;
///     win = win->getInstance();
///
///  Then to use functions from it://
///     int returnStatus = win->allocateWindow();


class WindowSingleton
{
public:

    // Singleton specific Functions
    static WindowSingleton* getInstance() {
        return (!m_instanceSingleton) ?
            m_instanceSingleton = new WindowSingleton :
            m_instanceSingleton;
    }

    // Basic functions
    void allocateWindow();
    sf::RenderWindow *getRwPtr();
void drawAll(sf::RenderTarget &rt, HView *hview);




private:

// Singleton specifics
    WindowSingleton() {  }
    ~WindowSingleton() { }
    // private copy constructor and assignment operator
    WindowSingleton(const WindowSingleton&);
    WindowSingleton& operator=(const WindowSingleton&);
    static WindowSingleton *m_instanceSingleton;




// Regular private members

    bool windowAllocated = false;
    std::string cn = "WindowSingleton.cpp";
    sf::RenderWindow *rwPtr = nullptr;               // Set when allocateWindow() is run

    bool fpsLockOn = true;  // Overridden by HConfig
    int fpsLock = 30;       // Overridden by HConfig



};

#endif
