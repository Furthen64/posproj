#include "HConfig.hpp"


/// \brief Loads everything into configMap
// (--)
bool HConfig::loadSettingsFromDefaultsIni()
{
    // Load all settings from "defaults.ini"

    std::cout << "Loading all the settings from \"defaults.ini\" ...\n";
    std::cout << "For now, hardcoded!\n";

    // Hardcoded:
    configMap.emplace("mouseSensitivity", "5");
    configMap.emplace("fpsLock", "30");

    return true;
}



// (--)
bool HConfig::addSetting(std::string _key, std::string _val, std::string category)
{
    configMap.emplace(_key, _val);
    categoryMap.emplace(_key, category);
    return true;
}


// (--)
std::string HConfig::getSetting(std::string _keySearch)
{
    std::map<std::string,std::string>::iterator it;

    it = configMap.find(_keySearch);
    if (it != configMap.end()) {
        return (*it).second;        // Dereference the found std::pair and get the "second" member, which is the value in a <key,value> pair!
    }

    std::cout << "WARNING: " << cn << " getSetting could not find " << _keySearch << "\n";
    return std::string("");
}