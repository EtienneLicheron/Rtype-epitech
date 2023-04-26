/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Entity
*/

#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__
#include <cstdint>
#define MAX_ENTITIES 1024
#define ENTITY_INT_SIZE std::uint32_t

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief Each entity has an unique ID in our program. <br />
             * This ID is used to identify an entity in the Manager class.
             */
            typedef ENTITY_INT_SIZE Entity;
        }
    }
}

#endif /* !__ENTITY_HPP__ */
