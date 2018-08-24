#include "Core.hpp"



Core::Core()
{
     WindowSingleton* dummy= nullptr;    // Absolutely needed for the WindowSingleton.hpp/cpp to compile.
    allocateSingletons();       // This is done once per application session
}


/// \brief A lifecycle is the entire thing from scratch, allocating memory, loading the map and setting up traffic.
RunResult *Core::lifecycle()
{
    RunResult *rres = new RunResult();

    std::cout << "lifecycle() stub\n";

    //

    //

    //

    //


    return rres;
}



RunResult *Core::run()
{
    RunResult *rres = new RunResult();

    std::cout << "run() stub\n";

    return rres;

}



void Core::allocateSingletons()
{

    std::cout << "allocateSingletons() stub\n";

    // WindowSingleton

    //  Create a handle wherever:
    WindowSingleton *win;
    win = win->getInstance();

    //Then to use functions from it://
    win->allocateWindow();



    // TextureSingleton

    // ConfigSingleton

}







