#include "Logger.hpp"

// Run this first! From main or something very early before doing logErr() or other
void Logger::bootLogger()
{

    std::cout << "bootLogger STUB OPEN FILE HANDLE!\n\n";
}


void Logger::logError(std::string str)
{
    std::cout << "ERROR " << str;
}
void logWarning(std::string str)
{
    std::cout << "Warning: " << str;
}
void log(std::string str)
{
    std::cout << str;
}






void logError(std::string);
void logWarning(std::string);
void log(std::string);
