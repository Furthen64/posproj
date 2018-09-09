// The documentation for HurkaLumos is mostly in the Docs\ folder.
//
// Some Tips & Trix can be found at       https://beta.etherpad.org/p/fat64_2       (2018-09)


#include "Core.hpp"

#include <stdexcept>
#include <math.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

#include <SFML/OpenGL.hpp>

#include "Singletons/Logger.hpp"

#include "Utilities/Utils.hpp"
#include "TextFactory.hpp"



// (--)
Core::Core()
{
    // This is done once per application session
    if(!allocateSingletons()) {
        throw std::runtime_error("ERROR: missing files - aborting with exception" );
    }


    // This is done once per application session, too!
    if(!setup()) {
        throw std::runtime_error("ERROR: core had issues running setup() - aborting with exception");
    }

    // Allocate all Core members
    canvas = new Canvas();

    // Store handy pointers in Core

    WindowSingleton *win;
    win = win->getInstance();

    std::cout << "hview: \n";
    win->hview = canvas->getHView();
    win->hview->dump();
}


/// \brief A lifecycle is the entire thing from scratch, allocating memory, loading the map and setting up traffic, THEN running the editor in run().
/// \brief After a run(), it looks at what happened in and responds accordingly.
/// \brief Maybe user wanted to quit, load a new map or maybe even clear the gameboard and start fresh with an empty map.
// (--)
RunResult *Core::lifecycle()
{
    RunResult *rres = new RunResult();

    rres = run();

    return rres;
}




/// \brief Loads up the Settings from the "defaults.ini" file. All settings can be reached from the singletong HConfig.
// (--)
bool Core::setup()
{
    hlog("core::setup()------------------------------------\n");
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
    hlog("------ setup done\n\n");


    return true;
}


void Core::resume() { isRunning = true; }
void Core::pause()  { isRunning = false; }



/// Not done, needs more consideration
void Core::resizeWindow()
{

    // The current Window width and height are
    //  * rwPtr->getSize().x
    //  * rwPtr->getSize().y


    win->hview->resizeViewToWindow();
    win->hview->dump();



}


// What are some more permanent markers I could use in the long run?
// Right now I am showing marker details for rotation of an OrMatrix into an Iso Matrix, not something I'd like to see later on.
// But, calculating new pixel positions from OrMatrix to Iso Matrix might need troubleshooting and then it'd be great if
// if could see the details of rotation.
// So angles and horizontal lines used to do it should be visible for the developer. (see flag showRotationMarkers in Core.hpp)

void Core::populateMarkers(RenderTree *rtree)
{
    std::cout << "STUB populateMarkers\n";
    //
    //sf::RectangleShape *horizontalLine = new sf::RectangleShape(sf::Vector2f(1280,2));
    //sf::RectangleShape clickedMarker(sf::Vector2f(4,4));
    //sf::RectangleShape rotatedMarker(sf::Vector2f(4,4));
    //sf::RectangleShape origoMarker(sf::Vector2f(4,4));



}




/// \brief Puts a couple of items in the rendertree, rendered close to the mouse cursor
void Core::populateDebugWindow(RenderTree *rtree, ScreenPos *mouse_scrpos, CanvasPos *mouse_cpos)
{
    int fontSizePx = 15;

    ScreenPos *topleft = mouse_scrpos->clone();
    topleft->y += win->hview->getTopLeft_y();
    topleft->x += win->hview->getTopLeft_x();


    // Window Position / Screen Position / SFML View position       ( SFML Screen Space )
    {
        sf::Text *textPtr = TextFactory::getTextShowingPosition(" ScreenPos ", fontSizePx, mouse_scrpos->y, mouse_scrpos->x , sf::Color(255,25,25));

        // "SFML Canvas Positioning", only viewed within the sf::View
        textPtr->setPosition(topleft->toVecf());

        rtree->addMiscText(textPtr);
    }

    // View Position (SFML Canvas Space)
    {
        topleft->y += 15;
        sf::Text *textPtr = TextFactory::getTextShowingPosition(" View      ", fontSizePx, win->hview->getTopLeft_y(), win->hview->getTopLeft_x(), sf::Color(111,111,100) );
        textPtr->setPosition(topleft->toVecf());
        rtree->addMiscText(textPtr);
    }


    // Equivalent Canvas Position
    {
        topleft->y += 15;
        sf::Text *textPtr = TextFactory::getTextShowingPosition(" CanvasPos ", fontSizePx, mouse_cpos->y, mouse_cpos->x, sf::Color(25,180,25) );
        textPtr->setPosition(topleft->toVecf());
        rtree->addMiscText(textPtr);
    }














}


/// \brief Makes a new run of the editor, called from lifeCycle()
/// \brief A window and all the singletons and managers are already allocated. run() will do the main loop of the editor,
/// \brief taking care of events, updating logic and drawing everything.
// (---)
RunResult *Core::run()
{


    /*/// Unit Testing
    {
        CanvasPos  *cpos = new CanvasPos(0,0);
        cpos->testCanvasPos();
    }
    */

    hlog("Core::run()-------------------------------------\n");



    /// Create and setup objects needed in this scope for the game loop
    RunResult *rres = new RunResult();
    sf::Event event;
    bool lmbPressed = false;
    win = win->getInstance();
    int clickIndex = 0;
    RenderTree *rendertree = new RenderTree();  // For all the Text objects and loose debug objects visible on screen

    /// Place our View at startup position
    win->hview->dump();
    win->hview->setTopLeft(-100,-100);



    /// Populate a couple of markers
    /*populateMarkers(rendertree);*/


    /// Debug Objects
    OrMatrix *orMat1 = new OrMatrix(5,10);
    orMat1->setPosition(new CanvasPos(184,184));


    IsoMatrix *isoMat1 = new IsoMatrix( orMat1 );

    isoMat1->rotateNDegCCW(45);




        /*bool rotEnabled = true;
    float rotAngle = 1;*/



    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Main loop
    /////////////////////////////////////////////////////////////////////////////////////////////////////////



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
                hlog(ind2 + " user clicked on close window.");
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

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            lmbPressed = false;  // Let go of LMB?
        }

        // Left mouse button pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lmbPressed && isRunning)
        {

            lmbPressed = true;
            sf::Vector2i mousePos_i = sf::Mouse::getPosition( *rwPtr );

            ScreenPos *mouse_scrpos = new ScreenPos(mousePos_i);
            CanvasPos *mouse_cpos   = scrpos_to_cpos(mouse_scrpos);




            // IsoMat1
            if(clickIndex == 0) {
                isoMat1->scale_y(0.5);
            }


            if(clickIndex == 1) {

                isoMat1->scale_y(2.0);
            }
            if(clickIndex == 2) {

                isoMat1->scale_y(0.5);
            }
            if(clickIndex == 3) {

            }
            clickIndex++;


            // Delete all other old text objects that we've created
            rendertree->clearMiscTexts();

            populateDebugWindow(rendertree, mouse_scrpos, mouse_cpos);


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

            win->hview->moveView( relativeY, relativeX );





            // Delete debug output before adding new one
            rendertree->clearMiscTexts();


            /*
            // Debug output, view topleft text
            {

                // Create text object from factory to display topleft of view
                sf::Text *textPtr = TextFactory::getText(hview->toString(),15,sf::Color(55,250,55,255));


                // sfml's "setPosition()" operates in sfml canvas space.
                // So we need to adjust with our view to always lock this to what is displayed on the Window.
                // We do this by offseting with view's topleft.


                textPtr->setPosition(hview->getTopLeft_x() + 6,
                                     hview->getTopLeft_y() + 4);



                // Add it to the render tree
                rendertree->addMiscText(textPtr);
            }

            */


        }



        /// Render

        rwPtr->clear();                 // Clear window
        rwPtr->pushGLStates();          // Needed for Gl Stuff below

        win->hview->drawAll(*rwPtr);            // Show the View boundary            Green
        canvas->drawAll(*rwPtr);           // Show the Canvas with its Grid     Blue


        // The Gameboard (orMatrix or isoMatrix )

       // orMat1->drawAll(*rwPtr);
      //  isoMat1->drawAll(*rwPtr);
//        CanvasPos *isoCenter = isoMat1->getMiddle_cpos();
        //isoCenter->drawAll(*rwPtr);

        // RenderTree contents
        for (std::vector<sf::Text *>::iterator textObjIt = rendertree->miscTexts.begin(); textObjIt!= rendertree->miscTexts.end(); ++textObjIt)
        {
            // Dereference our iterator into an sf::Text *
            sf::Text *textPtr = *textObjIt;

            if(textPtr == nullptr) {
                break;
            }

            // Now dereference our text and draw it
            rwPtr->draw( *textPtr);

        }






        //// OpenGL Extras
        rwPtr->popGLStates();       // from a PushGlStates further up




        // Draw dotted line
        /*
        glPushAttrib(GL_ENABLE_BIT);// glPushAttrib is done to return everything to normal after drawing
        glPushMatrix();

        glOrtho(hview->getTopLeft_x() , 1024 + hview->getTopLeft_x(), hview->getTopLeft_y() + 768, hview->getTopLeft_y(), 1, -1);

        glColor3f(0.0f,1.0f,1.0f);
        glLineStipple(10, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
            glVertex3f( glConv_x(origoMarker.getPosition().x), glConv_y(origoMarker.getPosition().y), 0.0f);
            glVertex3f( glConv_x(clickedMarker.getPosition().x), glConv_y(clickedMarker.getPosition().y), 0.0f);
        glEnd();


        glBegin(GL_LINES);
            glVertex3f( glConv_x(origoMarker.getPosition().x), glConv_y(origoMarker.getPosition().y), 0.0f);
            glVertex3f( glConv_x(rotatedMarker.getPosition().x), glConv_y(rotatedMarker.getPosition().y), 0.0f);
        glEnd();

        glPopMatrix();
        glPopAttrib();
        */





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







bool Core::closeSingletons()
{
    // Destroy all singletons
    /// destroy WindowSingleton
    /// destroy ResourceHolder

    /// destroy Logger
    Logger *logger;
    logger = logger->getInstance();
    logger->closeFilehandle();

    return true;
}
