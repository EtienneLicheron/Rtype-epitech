/*
** EPITECH PROJECT, 2022
** RType
** File description:
** AttributeServer
*/

#ifndef __ATTRIBUTESERVER_HPP__
#define __ATTRIBUTESERVER_HPP__

#include <string>
#include <cstdint>
#include <chrono>

#include "ECS/Entity.hpp"

namespace RType
{
    namespace Server
    {
        namespace ECS
        {
            /**
             * @brief A structure to define position
             */
            struct Position
            {
                float x;
                float y;
            };

            /**
             * @brief A structure to define size
             */
            struct Size
            {
                float width;
                float height;
            };

            /**
             * @brief A structure to define cooldown
             */
            struct Cooldown
            {
                long cooldown;
                std::chrono::milliseconds lastClick;
            };
        }
    }
}

#endif /* !__ATTRIBUTESERVER_HPP__ */
