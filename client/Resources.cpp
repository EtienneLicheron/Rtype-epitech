/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Resources
*/

#include "Resources.hpp"
#include <iostream>

std::string RType::Client::Resources::getPath(RType::Client::Resources::ResourceType type, std::string filename)
{
    // Get the binary path
    std::string path = "";
    #if defined(WIN32)
        char result[512];
        GetModuleFileName(NULL, result, 511);
        path = std::string(result);
        path = path.substr(0, path.find_last_of("\\/"));
        path += "\\Resources\\";
    #elif defined(__APPLE__)
        char result[512];
        uint32_t size = sizeof(result);
        if (_NSGetExecutablePath(result, &size) == 0)
            path = std::string(result);
        path = path.substr(0, path.find_last_of("/"));
        path += "/Resources/";
    #else
        char buff[512];
        ssize_t len = ::readlink("/proc/self/exe", buff, 511);
        if (len != -1) {
            buff[len] = '\0';
            path = std::string(buff);
        }
        path = path.substr(0, path.find_last_of("/"));
        path += "/Resources/";
    #endif
    // Get the resource path
    switch (type) {
        case RType::Client::Resources::Font:
            path += "Fonts";
            break;
        case RType::Client::Resources::Image:
            path += "Images";
            break;
        case RType::Client::Resources::Music:
            path += "Musics";
            break;
        case RType::Client::Resources::Sound:
            path += "Sounds";
            break;
        case RType::Client::Resources::Sprite:
            path += "Sprites";
            break;
    }
    #if defined(WIN32)
        path += "\\";
    #else
        path += "/";
    #endif
    path += filename;
    return (path);
}
