/*
** EPITECH PROJECT, 2022
** RType
** File description:
** IAttributeArray
*/

#ifndef __IATTRIBUTEARRAY_HPP__
#define __IATTRIBUTEARRAY_HPP__
#include "Entity.hpp"

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The one instance of virtual inheritance in the entire implementation of the ECS. <br />
             * An interface is needed so that the AttributeManager can tell a generic AttributeArray that an entity has been destroyed
             */
            class IAttributeArray
            {
            public:
                virtual ~IAttributeArray() = default;
                virtual void entityDestroyed(Entity entity) = 0;
            };
        }
    }
}

#endif /* !__IATTRIBUTEARRAY_HPP__ */
