#include "Core.hpp"

#include <stdexcept>
#include <math.h>


#include "Singletons/Logger.hpp"
#include "RenderTree.hpp"
#include "OrMatrix.hpp"
#include "TextFactory.hpp"



// (--)
Core::Core()
{
    // This is done once per application session
    if(!allocateSingletons()) {
         throw std::runtime_error( "ERROR: missing files - aborting with exception" );
    }


    // This is done once per application session, too!
    if(!setup()) {
        throw std::runtime_error("ERROR: core had issues running setup() - aborting with exception");
    }

    // Allocate all Core members
    canvas = new Canvas();


    // Store handy pointers in Core
    hview = canvas->getHView();
}


/// \brief A lifecycle is the entire thing from scratch, allocating memory, loading the map and setting up traffic, THEN running the editor in run().
/// \brief After a run(), it looks at what happened in and responds accordingly.
/// \brief Maybe user wanted to quit, load a new map or maybe even clear the gameboard and start fresh with an empty map.
// (--)
RunResult *Core::lifecycle()
{
    RunResult *rres = new RunResult();

    run();

    return rres;
}




/// \brief Loads up the Settings from the "defaults.ini" file. All settings can be reached from the singletong HConfig.
// (--)
bool Core::setup()
{
    std::cout << "core::setup()------------------------------------\n";
    // Read all the settings
    HConfig *cfg;
    cfg = cfg->getInstance();


    cfg->loadSettingsFromDefaultsIni();

    // Make some handy copies
    std::string settingStr = cfg->getSetting("mouseSensitivity");

    if(settingStr != "") {
        try{
            mouseSensitivity = std::stoi(settingStr);
        } catch( std::invalid_argument &e) {
            logErr(cn + " Could not convert string to int: \"" + settingStr + "\"\n");
        }
    }
    std::cout << " - setup done\n";


    return true;
}


void Core::resume() { isRunning = true; }
void Core::pause()  { isRunning = false; }
void Core::resizeWindow()
{

    // The current Window width and height are
    //  * rwPtr->getSize().x
    //  * rwPtr->getSize().y


    hview->resizeViewToWindow();


}


/// \brief Makes a new run of the editor, called from lifeCycle()
/// \brief A window and all the singletons and managers are already allocated. run() will do the main loop of the editor,
/// \brief taking care of events, updating logic and drawing everything.
// (---)
RunResult *Core::run()
{


    /// Unit Testing
    {
        CanvasPos  *cpos = new CanvasPos(0,0);
        cpos->testCanvasPos();
    }


    /// Create and setup objects needed in this scope for the game loop
    RunResult *rres = new RunResult();

    sf::Event event;

    bool lmbPressed = false;

    win = win->getInstance();

    OrMatrix *orMat1 = new OrMatrix(10,4);

    RenderTree *rendertree = new RenderTree();

    std::cout << ind1 << "run() started ***** \n";
    std::cout << ind1 << "{\n";

    //


    std::cout << "\n\n\n---------------run--------------------\n";

    while (rwPtr->isOpen())
    {

        if(!isRunning) {

            /// Paused
            // Check for Events
            while (rwPtr->pollEvent(event)) {
                if (event.type == sf::Event::GainedFocus) {
                    resume();
                }
            }

            continue;
        }



        /// Events

        while (rwPtr->pollEvent(event))
        {
            if (event.type == sf::Event::LostFocus) {
                pause();
            }

            if (event.type == sf::Event::GainedFocus) {
                resume();
            }

            if (event.type == sf::Event::Closed) {
                 // usecase: User clicked on Close Window
                    rres->retStr1 = "User clicked on Close Window.";
                    rres->intReturn = 0;
                    rres->quitresult =RR_QUIT;


                    rwPtr->close();

            }


            // Window Resize
            if( event.type == sf::Event::Resized) {
                resizeWindow();

            }
        }







        ///
        ///     LMB
        ///

        // Did you let go of LMB?
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            lmbPressed = false;
        }


        // Left mouse button pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lmbPressed && isRunning)
        {
            // Mouse click logic
            lmbPressed = true;
            sf::Vector2i mousePos_i = sf::Mouse::getPosition( *rwPtr );     // Get sfml mouse position



            // Delete all other old text objects that we've created
            rendertree->clearMiscTexts();

            // Display Window Position
            {
                std::string strMousePos = "window position(";
                strMousePos += std::to_string( mousePos_i.y );
                strMousePos += ", ";
                strMousePos += std::to_string( mousePos_i.x );
                strMousePos += ")";



                // Create text object from factory to display position
                sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(255,25,25,255));

                // Find out if we're outside the view scope

                textPtr->setPosition(sf::Vector2f(mousePos_i.x+ 15, mousePos_i.y-10));

                // Add it to the render tree
                rendertree->addMiscText(textPtr);
            }

            // Display Canvas Position  (where in the gamelogic did you click?)
            {


                int canvasYPos = mousePos_i.y + hview->getTopLeft_y();
                int canvasXPos = mousePos_i.x + hview->getTopLeft_x();

                std::string strMousePos = "canvas position(";
                strMousePos += std::to_string( canvasYPos  );
                strMousePos += ", ";
                strMousePos += std::to_string( canvasXPos );
                strMousePos += ")";

                // Create text object from factory to display position
                sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(25,25,255,255));

                // Find out if we're outside the view scope

                textPtr->setPosition(sf::Vector2f(mousePos_i.x+ 15, mousePos_i.y+2));

                // Add it to the render tree
                rendertree->addMiscText(textPtr);
            }



        }







        ///
        /// RMB
        ///

        // Right mouse button pressed - Pan the map
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {

            sf::Vector2i mousePos_i = sf::Mouse::getPosition( *rwPtr );

            int clickedY = mousePos_i.y;
            int clickedX = mousePos_i.x;

            int centerY = ceil(rwPtr->getSize().y/2);       // SCREEN HEIGHT / 2
            int centerX = ceil(rwPtr->getSize().x/2);       // SCREEN WIDTH / 2

            // Find out how far it is to that clicked position
            int relativeY = clickedY - centerY;

            // Adjust value for pan speed / mouse sensitivity and also use magic nrs for ratio of screen
            relativeY =  ( (float) relativeY * mouseSensitivity/80 );



            // Now, do x too
            int relativeX = clickedX - centerX;
            relativeX =  ( (float) relativeX * mouseSensitivity/120 );




            // Update the view against this relative motion
            hview->setTopLeft( hview->getTopLeft_y() + relativeY,
                               hview->getTopLeft_x() + relativeX);




        }




        /// Render

        rwPtr->clear();

        // The Three Layers?
        canvas->drawAll(*rwPtr);    // Blue
        hview->drawAll(*rwPtr);     // Green
        win->drawAll(*rwPtr);       // Red

        // The Gameboard (orMatrix or isoMatrix, whatever is visible )
        orMat1->drawAll(*rwPtr);


        // RenderTree contents
        for (std::vector<sf::Text *>::iterator textObjIt = rendertree->miscTexts.begin(); textObjIt!= rendertree->miscTexts.end(); ++textObjIt)
        {
            // Dereference our iterator into an sf::Text *
            sf::Text *textPtr = *textObjIt;

            if(textPtr == nullptr) {
                break;
            }

            // Now dereference that too, and draw it
            rwPtr->draw( *textPtr);



        }

        rwPtr->display();


    } // (window.isOpen)




    std::cout << "\n\n\n---------------run ENDED -------------\n";
    std::cout << ind1 << "} \n\n";

    return rres;

}



// (--)
bool Core::allocateSingletons()
{
    /// WindowSingleton
    WindowSingleton *win;
    win = win->getInstance();
    win->allocateWindow();
    this->rwPtr = win->getRwPtr();        // Now Core has a pointer to the Window, which is handy , but you can also use the singleton to fetch it anywhere



    /// ResourceHolder
    ResourceHolder* res;
    res = res->getInstance();
    if(!res->allocateFonts()) {
        return false;
    }

    /// Logger
    Logger *logger;
    logger = logger->getInstance();
    logger->bootLogger();


    return true;

}







