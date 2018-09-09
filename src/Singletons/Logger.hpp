#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
public:

    // Singleton specific Functions
    static Logger* getInstance() {
        return (!m_instanceSingleton) ?
            m_instanceSingleton = new Logger :
            m_instanceSingleton;
    }

    // Basic functions
    void bootLogger();  // Run this first! From main or something very early before doing logErr() or other

    void logError(std::string);
    void logWarning(std::string);
    void hlog(std::string);
    void closeFilehandle();


private:

    // Singleton specifics
        Logger() {  }
        ~Logger();
        // private copy constructor and assignment operator
        Logger(const Logger&);
        Logger& operator=(const Logger&);
        static Logger *m_instanceSingleton;


    // Regular private members
    std::string defaultLogFilename = "hurkalumo.log";
    std::ofstream filehandle;
    std::string cn = "Logger.cpp";
    int logCount = 0;
    int nrCountsUntilFlush = 5; // Performance thing, in case you are logging a lot, take this up a notch maybe to 50-100 or even 1000s
};

#endif
