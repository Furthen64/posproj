



// Docs in docs\ folder, lot of images! showing you whats what!
// Tips & Trix:         https://beta.etherpad.org/p/fat64_2


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
    std::cout << " - setup done\n\n";


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


// What are some more permanent markers I could use in the long run?
// Right now I am showing marker details for rotation of an OrMatrix into an IsoMatrix, not something I'd like to see later on.
// But, calculating new pixel positions from OrMatrix to IsoMatrix might need troubleshooting and then it'd be great if
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


    int clickIndex = 0;
    OrMatrix *orMat1 = new OrMatrix(10,10);
    orMat1->setPosition(new CanvasPos(-30,-30));

    IsoMatrix *isoMat1 = new IsoMatrix( orMat1 );
    isoMat1->setPosition(new CanvasPos(-30,-30));





    RenderTree *rendertree = new RenderTree();


    // Populate a couple of markers
    populateMarkers(rendertree);



LineRect *lineRect = new LineRect( new CanvasPos(0,0),
                                   new CanvasPos(46,46),
                                   new CanvasPos(92,0),
                                   new CanvasPos(46,-46) );

HRect *lineRect_boundingBox = new HRect(lineRect);




sf::RectangleShape horizontalLine (sf::Vector2f(1280,2));
sf::RectangleShape clickedMarker(sf::Vector2f(4,4));
sf::RectangleShape rotatedMarker(sf::Vector2f(4,4));
sf::RectangleShape origoMarker(sf::Vector2f(4,4));
origoMarker.setPosition(sf::Vector2f(0,0));
double beta = 45;   // Lets try rotate CCW n degrees





    std::cout << ind1 << "run() started ***** \n";
    std::cout << ind1 << "{\n";

    //



    //glShadeModel(GL_FLAT);


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



// IsoMat1
if(clickIndex == 1) {
    isoMat1->scale2x();
}
if(clickIndex == 2) {
    isoMat1->rotate45CCW();
}
clickIndex++;

            // Delete all other old text objects that we've created
            rendertree->clearMiscTexts();



            clickedMarker.setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x,
                                                   hview->getTopLeft_y() + mousePos_i.y ));




            //origoMarker.setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x - 200,
            //                                   hview->getTopLeft_y() + mousePos_i.y + 96));

            // Make a horizontal line just below the click



            horizontalLine.setPosition(sf::Vector2f(0,0));












            // Wishlist: make this easier on the developer:
{
// Display Window Position
{
    std::string strMousePos = "window click (";
    strMousePos += std::to_string( mousePos_i.y );
    strMousePos += ", ";
    strMousePos += std::to_string( mousePos_i.x );
    strMousePos += ")";



    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(255,25,25,255));

    // Wishlist:  Find out if we're outside the view scope

    // The position... iish.
    // mousePos_i.x + 15
    // and also offset for the view so it gets placed under the mousecursor at where the view is at ?
    // Makes sense? No? well yea... I need to make a function or something. Or not.
    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 15, hview->getTopLeft_y() + mousePos_i.y-10));


    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}



// View click Position
{
    int viewYPos = mousePos_i.y;
    int viewXPos = mousePos_i.x;

    std::string strMousePos = "view click   (";
    strMousePos += std::to_string( viewYPos  );
    strMousePos += ", ";
    strMousePos += std::to_string( viewXPos );
    strMousePos += ")";

    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(25,255,25,255));

    // Wishlist: Find out if we're outside the view scope

    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 15, hview->getTopLeft_y() + mousePos_i.y+2));

    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}



// Canvas Position  (where in the gamelogic did you click?)
{


    int canvasYPos = mousePos_i.y + hview->getTopLeft_y();
    int canvasXPos = mousePos_i.x + hview->getTopLeft_x();

    std::string strMousePos = "CanvasPos (";
    strMousePos += std::to_string( canvasYPos  );
    strMousePos += ", ";
    strMousePos += std::to_string( canvasXPos );
    strMousePos += ")";

    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(66,66,255,255));

    // Wishlist:  Find out if we're outside the view scope

    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 15, hview->getTopLeft_y() + mousePos_i.y+15));

    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}



bool showCalculationOfCanvasPos = false;

if(showCalculationOfCanvasPos) {
// View topleft Position
{

    int viewtopleftYPos = hview->getTopLeft_y();
    int viewtopleftXPos = hview->getTopLeft_x();

    std::string strMousePos = "  view topleft (";
    strMousePos += std::to_string( viewtopleftYPos  );
    strMousePos += ", ";
    strMousePos += std::to_string( viewtopleftXPos );
    strMousePos += ")";

    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(25,255,25,255));

    // Wishlist: Find out if we're outside the view scope

    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 250, hview->getTopLeft_y() + mousePos_i.y+2));
    //textPtr->setPosition(sf::Vector2f(mousePos_i.x+ 315, mousePos_i.y+2));

    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}





// + window click
{
    std::string strMousePos = "+ window click (";
    strMousePos += std::to_string( mousePos_i.y );
    strMousePos += ", ";
    strMousePos += std::to_string( mousePos_i.x );
    strMousePos += ")";


    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(255,25,25,255));

    // Wishlist: Find out if we're outside the view scope
    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 250, hview->getTopLeft_y() + mousePos_i.y+15));


    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}

// Canvas Position  (where in the gamelogic did you click?)
{


    int canvasYPos = mousePos_i.y + hview->getTopLeft_y();
    int canvasXPos = mousePos_i.x + hview->getTopLeft_x();

    std::string strMousePos = "= canvas click (";
    strMousePos += std::to_string( canvasYPos  );
    strMousePos += ", ";
    strMousePos += std::to_string( canvasXPos );
    strMousePos += ")";

    // Create text object from factory to display position
    sf::Text *textPtr = TextFactory::getText(strMousePos,15,sf::Color(66,66,255,255));

    // Wishlist:  Find out if we're outside the view scope

    textPtr->setPosition(sf::Vector2f(hview->getTopLeft_x() + mousePos_i.x+ 250, hview->getTopLeft_y() + mousePos_i.y+30));

    // Add it to the render tree
    rendertree->addMiscText(textPtr);
}
} // (Show calc of canvaspos = true)
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




            // Delete debug output before adding new one
            rendertree->clearMiscTexts();


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




        }

// Get the angle from horizontal line to clicked marker from origo marker
/*double alpha = asin ((double) a/c) * 180.0 / PI;
if (errno == EDOM) {
    logErr("asin failed!\n");
}*/





//                    c              _ .
//                            _   -    |
//                 _     -             |  a
//           _-________________________|
//                           b
//
//






// Solve all sides of the triangle
float a=  (origoMarker.getPosition().y - clickedMarker.getPosition().y);
float b=   (clickedMarker.getPosition().x - origoMarker.getPosition().x);
//float c=  abs( sqrt(a*a + b*b));

//std::cout << "                    beta = " << beta << "\n";

float previous_x = b;
float previous_y = -a;

float rotated_x = rotateCCW_x(previous_x, previous_y, beta);
float rotated_y = rotateCCW_y(previous_x, previous_y, beta);

//std::cout << "a=" << a  << " b=" << b << " c= " << c << " alpha=" << alpha << " | prev_pos = (" << previous_y << ", " << previous_x << ") | new_pos = (" << rotated_y << ", " << rotated_x << ")\n";


rotatedMarker.setPosition(sf::Vector2f(rotated_x, rotated_y));




        /// Render

        rwPtr->clear();

        rwPtr->pushGLStates();




        // The Three Layers?

        // Fixme, add hview to canvas too
        hview->drawAll(*rwPtr);            // Green
        win->drawAll(*rwPtr, hview);       // Red

        // The Gameboard (orMatrix or isoMatrix, whatever is visible )
        //orMat1->drawAll(*rwPtr);
        isoMat1->drawAll(*rwPtr);



        // Misc Debug output
        rwPtr->draw(clickedMarker);
        rwPtr->draw(origoMarker);
        rwPtr->draw(horizontalLine);
        rwPtr->draw(rotatedMarker);





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


        canvas->drawAll(*rwPtr);    // Blue

        lineRect->drawAll(*rwPtr);

        lineRect_boundingBox->drawAll(*rwPtr);


        //// OpenGL Extras
        rwPtr->popGLStates();       // from a PushGlStates further up




// Draw dotted line

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







