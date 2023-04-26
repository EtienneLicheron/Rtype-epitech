/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Resources
*/

#ifndef __RESOURCES_HPP__
    #define __RESOURCES_HPP__
    #include <filesystem>
    #include <string>
    #include "Exception.hpp"
    #define _WINSOCKAPI_
    #if defined(WIN32)
        #include <winsock2.h>
        #include <windows.h>
    #elif defined(__APPLE__)
        #include <mach-o/dyld.h>
    #else
        #include <unistd.h>
    #endif

namespace RType {
    namespace Client {
        namespace Resources {
            enum ResourceType {
                Font,
                Image,
                Music,
                Sound,
                Sprite
            };

            /**
             * @brief Get the path of a resource (needed for cross-platform)
             *
             * @param type The type of the resource
             * @param filename The filename of the resource
             */
            std::string getPath(ResourceType type, std::string filename);
        }
    }
}

#endif /* !__RESOURCES_HPP__ */
