#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H


#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"



/// Example usage:
///  Create a handle wherever:
///     ResourceHolder *res;
///     res = res->getInstance();




class ResourceHolder
{
public:

    // Singleton specific Functions
    static ResourceHolder* getInstance() {
        return (!m_instanceSingleton) ?
            m_instanceSingleton = new ResourceHolder :
            m_instanceSingleton;
    }

    // Basic functions
    bool allocateFonts();


    // Basic members
    sf::Font *arialFont;
    sf::Font *fixedsysFont;



private:

    // Singleton specifics
        ResourceHolder() {  }
        ~ResourceHolder() { }
        // private copy constructor and assignment operator
        ResourceHolder(const ResourceHolder&);
        ResourceHolder& operator=(const ResourceHolder&);
        static ResourceHolder *m_instanceSingleton;




    // Regular private members
        std::string cn = "ResourceHolder.cpp";




};

#endif
