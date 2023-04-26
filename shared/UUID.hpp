/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UUID
*/

#ifndef __UUID_HPP__
#define __UUID_HPP__
#include <string>
#include <random>
#include <sstream>

namespace RType
{
    namespace Shared
    {
        namespace UUID
        {
            /**
             * @brief Generate a new UUID
             *
             * @return std::string The new UUID
             */
            std::string generate();
            /**
             * @brief Check if the UUID is valid
             *
             * @param uuid The UUID to check
             * @return bool True if the UUID is valid, false otherwise
             */
            bool isValid(std::string uuid);
        }
    }
}

#endif /* !__UUID_HPP__ */
