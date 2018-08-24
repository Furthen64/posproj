#include <SFML/Graphics.hpp>

#include "Core.hpp"

#include <iostream>



// Absolutely needed for the Singletons to compile
WindowSingleton* WindowSingleton::m_instanceSingleton = nullptr;        // This static member needs to exist super early




int main(int argc, char **argv)
{

        RunResult *rres  = nullptr;

        Core *core = new Core();

        rres = core->lifecycle();

        rres->dump();

        return 0;
}
