#include <SFML/Graphics.hpp>

#include "Core.hpp"
#include "Utilities/Utils.hpp"

#include <iostream>

// Absolutely needed for the Singletons to compile, the static member "m_instanceSingleton" needs to exist super early
HConfig *HConfig::m_instanceSingleton = nullptr;
WindowSingleton *WindowSingleton::m_instanceSingleton = nullptr;
ResourceHolder *ResourceHolder::m_instanceSingleton = nullptr;
Logger *Logger::m_instanceSingleton = nullptr;

int main(int argc, char **argv)
{
    RunResult *rres  = nullptr;

    Core *core = new Core();

    rres = core->lifecycle();

    if(rres != nullptr) {
        rres->dump();
    }

    // Close down the singletons
    core->closeSingletons();

    return 0;
}
