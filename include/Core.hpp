#ifndef CORE_H
#define CORE_H


#include <iostream>
#include <string>

#include "../src/Singletons/WindowSingleton.hpp"        // <== SView
#include "../src/Singletons/ResourceHolder.hpp"

#include "Canvas.hpp"
#include "CanvasPos.hpp"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum RUNRESULTS { RR_QUIT, RR_LOADNEWMAP, RR_NEWMAP };


/// \brief Return class, used by Core::run() to see what happened after a run was completed

class RunResult
{
public:
    RunResult() {}
    RunResult(int _intReturn)
    {
        intReturn = _intReturn;
    }

    void dump()
    {
        std::cout << "RunResult\n";
        std::cout << "   quitresult= " << quitresult << "\n";
        std::cout << "   intReturn = " << intReturn << "\n";
        std::cout << "   retStr1   = \"" << retStr1 << "\"\n";
        std::cout << "   retStr2   = \"" << retStr2 << "\"\n";
        std::cout << "   retStr3   = \"" << retStr3 << "\"\n";
    }

    int quitresult  = 0;        // See Enum RUNRESULTS
    int intReturn   = 0;
    char charReturn = 0;

    std::string retStr1 ;       // Usually used for filenames
    std::string retStr2 ;
    std::string retStr3 ;


private:

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hey there new developer!
//
// Core allocates all the singletons and managers, and also contains the main loop.
// The order is basically
//      Allocate all things
//      Setup
//      Enter a LifeCycle
//              Run()
//              Something happens... User loads new map
//      Enter a new Lifecycle
//              Run()
//              user restarts map
//              Run()


class Core
{
public:

    Core();

    bool allocateSingletons();

    int setup();

    RunResult *lifecycle();

    RunResult *run();

    void resume();
    void pause();
    void resizeWindow();




private:

    sf::RenderWindow *rwPtr = nullptr;       // Set after we allocateWindow from the singleton, done in Core() constructor

    WindowSingleton *win;                 // win = win->getInstance(); to use it!

    Canvas *canvas = nullptr;             // See Core()
    HView *hview = nullptr;               // See Core()


    bool isRunning = true;              // Used for Pause and Resume

    std::string cn = "Core.cpp";
    std::string ind1 = "";
    std::string ind2 = "";
    std::string ind3 = "";
};



#endif
