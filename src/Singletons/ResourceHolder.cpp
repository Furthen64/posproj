#include "ResourceHolder.hpp"


#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <utility>

#include "Utilities/Utils.hpp"


/// \brief Clears all already loaded textures and loads all textures as listed in "textures.txt"
/// \return 0 on OK, -1 on failure
// (--)
int ResourceHolder::loadTextures()
{

    // Clear all the old ones
    textureMap.clear();
    loadedTextures = false;


    sf::Texture txt;
    bool failed = false;


    // Read a textfile with all the textures listed in it

    std::string texturesFileList = getFullUri("data\\textures.txt");
    std::string line;
    std::string textureFullUri;
    std::string textureName;
    std::list<std::string> textureList;




    std::ifstream myfile (texturesFileList);
    if (myfile.is_open())
    {
       while ( myfile.good() )
       {
          getline (myfile,line);

          // Is it a whitespace line? ignore it
          if(line != "") {

                  // Create the correct names for the datastructure

                  textureName = "data\\textures\\";
                  textureName += line;
                  textureName += ".png";

                  textureFullUri = getFullUri(textureName);



                  if(!txt.loadFromFile(textureFullUri)) {
                        std::cout << " texture load from file failed with \"" << textureFullUri << "\"\n";
                        failed = true;

                  }


                  // Put it in the ADT
                  pushTexture(line, txt);

            }

        }

        myfile.close();

    }  else {
        std::cout << "ERROR " << cn << " Unable to open file " << texturesFileList << "\n";
        return -1;
    }

    if(failed) {
       return -1;
    }

    loadedTextures = true;
    return 0;
}


// Converts the integer to string version of textures in the library
// (--)
std::string ResourceHolder::getTextureNameByIndex(int nr)
{
    switch(nr){
        case 0: return "GRASS001";

        case 1: return "HOUSE001";
        case 2: return "HOUSE002";
        case 3: return "HOUSE003";
        case 4: return "HOUSE004";
        case 5: return "HOUSE005";
        case 6: return "HOUSE006";
        case 7: return "HOUSE007";
        /*case 8: return "HOUSE008";
        case 9: return "HOUSE009";
        case 10: return "HOUSE010";*/

        case 101: return "ROAD001";
        case 102: return "ROAD002";
        case 103: return "ROAD003";
        case 104: return "ROAD004";
        case 105: return "ROAD005";
        case 106: return "ROAD006";
        case 107: return "ROAD007";
        case 108: return "ROAD008";
        case 109: return "ROAD009";
        case 110: return "ROAD010";

        case 301: return "TREE001";
        case 302: return "TREE002";
        case 303: return "TREE003";




        case 401: return "BUS001";

        case 501: return "GRID1";
        case 502: return "GRID2";

        case 551: return "GRASS1";
        case 552: return "GRASS2";


        default:
            std::cout << cn << " could not find texture nr = " << nr << "\n";
            return "";
    }



    return "";
}





/// FIXME! Needs error handling if we can't find the key
/// (--)
sf::Texture ResourceHolder::getTexture(std::string _key)
{

    if(textureMap.size() <1) {
        std::cout << "ERROR " << cn << " The textures have not yet been loaded, and the program wants to find a texture. System failure!\n";
        throw std::exception();
    }
    return textureMap[_key];
}



/// Add texture object into the internal storage
/// (-+)
void ResourceHolder::pushTexture(std::string _name, sf::Texture _texture)
{
    textureMap.insert( {_name, _texture});
}

void ResourceHolder::dump()
{
    std::cout << "\n\nResourceHolder.dump()\n----------------------\n{\n";

    for( std::unordered_map<std::string, sf::Texture>::const_iterator it = textureMap.begin(); it != textureMap.end(); ++it)
    {
        std::pair<std::string, sf::Texture> pair1 = (*it);

        std::cout << " texturename=" << (std::string) pair1.first << "\n";
    }

    std::cout << "}\n";
}





/// Given a key and an already loaded texture, put it into the internal storage
//(--) buggy for now 2018-07
bool ResourceHolder::applyTexture(std::string textureName, sf::Texture *texture, bool startGLContext)
{
    bool result = false;

    std::unordered_map<std::string, sf::Texture>::const_iterator got = textureMap.find(textureName);

    if(got == textureMap.end()) {
        std::cout << "ERROR " << cn << " applyTexture could not find the texture: \"" << textureName << "\" in the textureMap!\n";

        dump();

    } else {

        // Dereference our *texture and set it to the texture we have loaded into the hashmap

        (*texture) = textureMap[textureName];       // #CR24 - This thing needs a GL Context to work. Without it it will spit out GL_FLUSH errors!


        result = true;
    }

    return result;
}







/// \brief Update a texture inside "textureMap"
/// \brief Example: supply id=001 and it looks up the texture name "HOUSE001"  and then assigns that to the texture pointer
/// \return true on OK, false on failure
// (-+)
bool ResourceHolder::applyTextureById(unsigned int _textureId, sf::Texture *texture, bool startGLContext)
{
    bool result = false;

    if(!loadedTextures) {
        return false;
    }


    // Convert the integer to the right string name

    std::string _textureName = getTextureNameByIndex(_textureId);

    if(_textureName == "") {
        std::cout << "ERROR " << cn << " applyTextureById cannot find texturename by id " << _textureId << "\n";
        return false;
    }


    // Now find it by searching for the string
    std::unordered_map<std::string, sf::Texture>::const_iterator got = textureMap.find(_textureName);

    if(got == textureMap.end()) {
        std::cout << "ERROR " << cn << " applyTextureById could not find the texture: \"" << _textureName << "\"!\n";
    } else {
        // Dereference our *texture and set it to the texture we have loaded into the hashmap
        (*texture) = textureMap[_textureName];
        result = true;
    }

    return result;
}



// (TEST)
std::unordered_map<std::string,sf::Texture> ResourceHolder::getTextureMap()
{
    std::cout << "getTextureMap() not done! Makes a shallow copy?\n";
    return textureMap;
}



// (--)
int ResourceHolder::nrOfTextures()
{
    return textureMap.size();
}


bool ResourceHolder::allocateFonts()
{

    //  ARIAL
    {
        arialFont = new sf::Font();


        /*
        "The loadFromFile function can sometimes fail with no obvious reason.

        First, check the error message that SFML prints to the standard output (check the console).
        If the message is unable to open file, make sure that the working directory (which is the
        directory that any file path will be interpreted relative to) is what you think it is:

        When you run the application from your desktop environment, the working directory is the executable folder.
        However, when you launch your program from your IDE (Visual Studio, Code::Blocks, ...) the working directory
        might sometimes be set to the project directory instead. This can usually be changed quite easily in the project settings"
        */


        // Load from a font file on disk
        if (!arialFont->loadFromFile("../data/fonts/arial.ttf"))
        {
            std::cout << "ERROR " << cn << " could not find font arial.ttf!\n";
            return false;
        }
    }


    // FIXEDSYS
    {
        fixedsysFont = new sf::Font();
        if(!fixedsysFont->loadFromFile("../data/fonts/FSEX300.ttf")) {
            std::cout << "ERROR " << cn << " could not find font FSEX300.ttf!\n";
            return false;
        }
    }
    return true;
}

