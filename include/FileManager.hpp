#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../src/Singletons/ResourceHolder.hpp"
#include "HurkaMap.hpp"
#include "Constants.hpp"
#include "Utilities/Utils.hpp"

class FileManager
{
public:
    FileManager();

    bool verifyFile(std::string fullUri, int *rows, int *cols, int debugLevel);

    HurkaMap *readRegularFile(std::string fullUri, int debugLevel, IsoMatrix *);

    bool saveRegularFile(std::string fullUri, int debugLevel, HurkaMap *, IsoMatrix *);

    void printWorkingDir();


    static std::string convertToOutputString(int nr)
    {
        std::string str = "000";


        if(nr <100) {
            if(nr <10) {
                // 0-9

                str = "00";
                str += std::to_string(nr);



            } else {
                // 10->99
                str = "0";
                str += std::to_string(nr);
            }
        } else {
            return std::to_string(nr);
        }


        return str;
    }

private:

    std::string cn = "FileManager.cpp";
};

#endif
