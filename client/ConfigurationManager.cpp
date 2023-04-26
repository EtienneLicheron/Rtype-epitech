/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ConfigurationManager
*/

#include "ConfigurationManager.hpp"
#if DEBUG_CONFMANAGER
    #include <iostream>
#endif

RType::Client::ConfigurationManager::ConfigurationManager()
{
    // Open and create if not exist
    std::fstream file(CONFIG_FILE, std::fstream::in | std::fstream::app);
    if (!file.good())
        throw RType::Shared::Exception("Can't create config file");
    // if the file is empty, we create the default values
    if (getValue("initialized") == "") {
        #if DEBUG_CONFMANAGER
            std::cout << "Config file is empty, creating default values" << std::endl;
        #endif
        file.clear();
        file << "# R-Type configuration file" << std::endl;
        file << "# DON'T MODIFY THIS FILE MANUALLY, OR UNKNOWN BEHAVIOR COULD HAPPEN" << std::endl;
        file.close();
        setValue("initialized", "true");
        setValue("menuMusicVolume", "25");
        setValue("gameMusicVolume", "25");
        setValue("gameSoundsVolume", "25");
        setValue("username", "");
        setValue("address", "");
        setValue("port", "");
    }
    else {
        file.close();
        #if DEBUG_CONFMANAGER
            std::cout << "Config file is not empty, just loading the values inside memories" << std::endl;
        #endif
    }
    if (getValue("initialized") != "true")
        throw RType::Shared::Exception("Config file is corrupted");
    if (getValue("menuMusicVolume") == "" || std::stoi(getValue("menuMusicVolume")) < 0 || std::stoi(getValue("menuMusicVolume")) > 100)
        throw RType::Shared::Exception("Invalid menu music volume (MUST be >= 0 && <= 100");
    if (getValue("gameMusicVolume") == "" || std::stoi(getValue("gameMusicVolume")) < 0 || std::stoi(getValue("gameMusicVolume")) > 100)
        throw RType::Shared::Exception("Invalid game music volume (MUST be >= 0 && <= 100");
    if (getValue("gameSoundsVolume") == "" || std::stoi(getValue("gameSoundsVolume")) < 0 || std::stoi(getValue("gameSoundsVolume")) > 100)
        throw RType::Shared::Exception("Invalid game sounds volume (MUST be >= 0 && <= 100");
    #if DEBUG_CONFMANAGER
        for (auto &it : _values) {
            std::cout << "Key: " << it.first << " Value: " << it.second << std::endl;
        }
    #endif
}

RType::Client::ConfigurationManager::~ConfigurationManager()
{
}

std::string RType::Client::ConfigurationManager::getValue(std::string key)
{
    #if DEBUG_CONFMANAGER
        std::cout << "Getting value for key \"" << key << "\"" << std::endl;
    #endif
    if (_values.find(key) != _values.end())
        return (_values.at(key));
    std::regex regex(key + " = \"(.*)\";");
    std::smatch match;
    std::string line;
    std::fstream file(CONFIG_FILE, std::fstream::in);
    if (!file.good())
        throw RType::Shared::Exception("Can't open config file");
    while (std::getline(file, line)) {
        if (std::regex_search(line, match, regex)) {
            #if DEBUG_CONFMANAGER
                std::cout << "Found value: " << match[1] << std::endl;
            #endif
            _values[key] = match[1];
            return (match[1]);
        }
    }
    return ("");
}

void RType::Client::ConfigurationManager::setValue(std::string key, std::string value)
{
    #if DEBUG_CONFMANAGER
        std::cout << "Setting value \"" << value << "\" for key \"" << key << "\"" << std::endl;
    #endif
    std::fstream file(CONFIG_FILE, std::fstream::in | std::fstream::out);
    if (!file.good())
        throw RType::Shared::Exception("Can't open config file");
    _values[key] = value;
    std::string fileContent;
    std::string line;
    std::regex regex(key + " = \"(.*)\";");
    std::smatch match;
    bool found = false;
    while (std::getline(file, line)) {
        if (std::regex_search(line, match, regex)) {
            #if DEBUG_CONFMANAGER
                std::cout << "Found value: " << match[1] << std::endl;
            #endif
            line = key + " = \"" + value + "\";";
            found = true;
        }
        else if (line == "")
            continue;
        fileContent += line + "\n";
    }
    if (!found)
        fileContent += key + " = \"" + value + "\";\n";
    file.clear();
    file.seekp(0);
    file << fileContent;
    file.close();
    #if DEBUG_CONFMANAGER
        std::cout << "Setted value \"" << value << "\" for key \"" << key << "\"" << std::endl;
    #endif
}
