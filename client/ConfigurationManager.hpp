/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ConfigurationManager
*/

#ifndef __CONFIGURATIONMANAGER_HPP__
#define __CONFIGURATIONMANAGER_HPP__
#define CONFIG_FILE ".rtype.config"
#define DEBUG_CONFMANAGER false
#include "Exception.hpp"
#include <fstream>
#include <regex>
#include <string>
#include <map>

namespace RType
{
    namespace Client
    {
        /**
         * @brief This class will handle configuration file, it will load it, save it, etc...
         *
         * @note This class is a singleton, and all the methods can throw an exception (in case the file can't be opened)
         */
        class ConfigurationManager
        {
        public:
            /**
             * @brief The constructor will open the config file and load it, with default values if the file doesn't exist
             */
            ConfigurationManager();
            ~ConfigurationManager();
            /**
             * @brief Get a value from the config file
             *
             * @param key The key of the value
             * @return std::string The value
             */
            std::string getValue(std::string key);
            /**
             * @brief Set a value in the config file
             *
             * @param key The key of the value
             * @param value The value
             */
            void setValue(std::string key, std::string value);

        private:
            /**
             * @brief Pair key/values of the config file
             */
            std::map<std::string, std::string> _values;
        };
    }
}

#endif /* !__CONFIGURATIONMANAGER_HPP__ */
