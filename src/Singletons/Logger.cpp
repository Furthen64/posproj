#include "Logger.hpp"

// Run this first! From main or something very early before doing logErr() or other
void Logger::bootLogger()
{
    filehandle.open(defaultLogFilename);
}


Logger::~Logger()
{
    filehandle.close();
}

void Logger::logError(std::string str)
{
    std::cout << "ERROR " << str;
    filehandle << "E " << str;

    if(logCount++ > nrCountsUntilFlush) {
        filehandle.flush();
        logCount = 0;
    }
}
void Logger::logWarning(std::string str)
{
    std::cout << "Warning: " << str;
    filehandle << "W " << str;

    if(logCount++ > nrCountsUntilFlush) {
        filehandle.flush();
        logCount = 0;
    }


}
void Logger::hlog(std::string str)
{
    std::cout << str;
    filehandle <<  "  " << str;

    if(logCount++ > nrCountsUntilFlush) {
        filehandle.flush();
        logCount = 0;
    }
}


void Logger::closeFilehandle()
{
    filehandle.close();
}
