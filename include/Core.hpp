#ifndef CORE_H
#define CORE_H


#include <iostream>
#include <string>

#include "../src/Singletons/WindowSingleton.hpp"        // <== SView

#include "Canvas.hpp"








enum RUNRESULTS { RR_QUIT, RR_LOADNEWMAP, RR_NEWMAP };


/// \brief Return class, used by Core::run() to see what happened after a run was completed

class RunResult
{
public:
    RunResult() {}
    ~RunResult() {}

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



class Core
{
public:

    Core();

    RunResult *lifecycle();

    RunResult *run();

    void resume();
    void pause();
    void resizeWindow();


    int setup();


    // Specific

    void allocateSingletons();


private:


    WindowSingleton* dummy= nullptr;    // Absolutely needed for the WindowSingleton.hpp/cpp to compile.

    sf::RenderWindow *wPtr = nullptr;       // Set after we allocateWindow from the singleton, done in Core() constructor

    sf::View *view = nullptr;

    Canvas *canvas = nullptr;


    bool isRunning = true;              // Used for Pause and Resume

    std::string cn = "Core.cpp";
    std::string ind1 = "";
    std::string ind2 = "";
    std::string ind3 = "";
};



#endif
