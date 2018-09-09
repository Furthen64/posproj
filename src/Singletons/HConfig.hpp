#ifndef HCONFIG_H
#define HCONFIG_H

#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "Constants.hpp"



/// Example usage:
///  Create a handle wherever:
///     Config *cfg;
///     cfg = cfg->getInstance();

class HConfig
{
public:

    // Singleton specific Functions
    static HConfig* getInstance() {
        return (!m_instanceSingleton) ?
            m_instanceSingleton = new HConfig :
            m_instanceSingleton;
    }

    // Basic functions
    bool loadSettingsFromDefaultsIni();
    bool addSetting(std::string _key, std::string _val, std::string category);
    std::string getSetting(std::string _keySearch);

private:

    // Singleton specifics
    HConfig() {  }
    ~HConfig() { }
    // private copy constructor and assignment operator
    HConfig(const HConfig&);
    HConfig& operator=(const HConfig&);
    static HConfig *m_instanceSingleton;


    // Regular private members
    std::string cn = "HConfig.cpp";

    std::map<std::string, std::string> configMap;     // Main data structure for storing the <key,val> pairs
    std::map<std::string, std::string> categoryMap;   // Example of category: "INPUT_SETTINGS", could have settings like: {"mouseSensitivy=200"}



};

#endif
