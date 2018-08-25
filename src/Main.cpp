#include <SFML/Graphics.hpp>

#include "Core.hpp"

#include <iostream>



// Absolutely needed for the Singletons to compile, the static member "m_instanceSingleton" needs to exist super early
WindowSingleton* WindowSingleton::m_instanceSingleton = nullptr;


int main(int argc, char **argv)
{
    RunResult *rres  = nullptr;

    Core *core = new Core();

    core->lifecycle();

    rres->dump();

    return 0;
}
