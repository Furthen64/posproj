#include "Core.hpp"

#include "OrMatrix.hpp"


#include <math.h>


// (--)
Core::Core()
{
    allocateSingletons();               // This is done once per application session
    canvas = new Canvas();
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
    RunResult *rres = new RunResult();

    sf::Event event;

    bool lmbPressed = false;

    win = win->getInstance();

    OrMatrix *orMat1 = new OrMatrix(20,20);


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





        // Left mouse button pressed,

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !lmbPressed && isRunning)
        {
            lmbPressed = true;

            // Get mouse position
            sf::Vector2i mousePos_i = sf::Mouse::getPosition( *rwPtr );

            // What does it look like now that I am using SView?
            std::cout << ind2 << " - lmb pressed at sfml:getPosition = " << mousePos_i.y << ", " << mousePos_i.x << "\n";

            // convert it to our type of position

        }







        ///
        /// RMB
        ///

        // Right mouse button pressed - Pan the map

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
        }





        /// Render

        rwPtr->clear();


        // The Three Layers?



        hview->drawAll(*rwPtr);
        canvas->drawAll(*rwPtr);
        win->drawAll(*rwPtr);




        // The Gameboard (orMatrix or isoMatrix, whatever is visible )

        //orMat1->drawAll(*rwPtr);



        rwPtr->display();


    } // (window.isOpen)




    std::cout << "\n\n\n---------------run ENDED -------------\n";
    std::cout << ind1 << "} \n\n";

    return rres;

}



// (--)
void Core::allocateSingletons()
{
    /// WindowSingleton
    WindowSingleton *win;
    win = win->getInstance();
    win->allocateWindow();
    this->rwPtr = win->getRwPtr();        // Now Core has a pointer to the Window, which is handy , but you can also use the singleton to fetch it anywhere


    /// TextureSingleton



    /// ConfigSingleton

}







