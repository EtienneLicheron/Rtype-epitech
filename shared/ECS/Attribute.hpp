/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Attribute
*/

#ifndef __ATTRIBUTE_HPP__
#define __ATTRIBUTE_HPP__

#define MAX_ATTRIBUTES 64

#include <string>
#include <cstdint>
#include <chrono>

#include "Entity.hpp"

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief An attribute is a piece of data for an entity, per example a position, which is a 2D vector. <br />
             * Each attribute is an unique ID in our program.
             */
            typedef std::uint8_t AttributeType;

            /**
             * @brief A structure to define entity type
             */
            struct EntityType
            {
                std::string value;
            };

            /**
             * @brief A structure to define speed
             */
            struct Speed
            {
                float value;
            };

            /**
             * @brief A structure to define health - Client or Server
             */
            struct Health
            {
                int value;
            };

            /**
             * @brief A structure to define cooldown - Client or Server
             */
            struct Cooldown
            {
                long cooldown;
                std::chrono::milliseconds lastClick;
            };

            struct Tag
            {
                std::string value;
            };

            struct Velocity
            {
                float x;
                float y;
            };

            struct Clock
            {
                std::chrono::seconds lastRequest;
                float duration;
            };
        }
    }
}

#endif /* !__ATTRIBUTE_HPP__ */
