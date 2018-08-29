#include "ResourceHolder.hpp"

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

