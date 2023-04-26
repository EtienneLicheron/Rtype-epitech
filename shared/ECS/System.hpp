/*
** EPITECH PROJECT, 2022
** RType
** File description:
** System
*/

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__
#include "Entity.hpp"
#include <set>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The system is just a set of entities.
             */
            class System
            {
            public:
                /**
                 * @brief We choose a set here, because list and array are too slow, the benchmark shows that a set is the fastest. (since we only have int inside it)
                 *
                 */
                std::set<Entity> entities;
            };
        }
    }
}

#endif /* !__SYSTEM_HPP__ */
