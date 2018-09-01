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
void log(std::string);


private:

    // Singleton specifics
        Logger() {  }
        ~Logger() { }
        // private copy constructor and assignment operator
        Logger(const Logger&);
        Logger& operator=(const Logger&);
        static Logger *m_instanceSingleton;


    // Regular private members
        std::string cn = "Logger.cpp";
};

#endif
