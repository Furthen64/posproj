#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H


#include <string>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"




/// Inside the game code you use strings to find textures, "GRASS001".
/// The maps themselves use simple numbers (001,002) for ease of writing maps but don't use them here in the code.



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


int loadTextures();

void dump();

void pushTexture(std::string _name, sf::Texture _texture);
sf::Texture getTexture(std::string _key);

bool applyTexture(std::string textureName, sf::Texture *texture, bool startGLContext);
bool applyTextureById(unsigned int _textureId, sf::Texture *texture, bool startGLContext);

std::string getTextureNameByIndex(int nr);  // Only used by Map to get the string name

std::unordered_map<std::string,sf::Texture> getTextureMap();

int nrOfTextures();




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
bool loadedTextures = false;
std::unordered_map<std::string,sf::Texture> textureMap;



};

#endif
