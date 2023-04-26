/*
** EPITECH PROJECT, 2022
** RType
** File description:
** EntityManager
*/

#ifndef __ENTITYMANAGER_HPP__
#define __ENTITYMANAGER_HPP__
#include "../Exception.hpp"
#include "Signature.hpp"
#include "Entity.hpp"
#include <queue>
#include <array>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The EntityManager class is in charge to distribute the entities ID and keep records of which entity is in use. <br />
             */
            class EntityManager
            {
            public:
                /**
                 * @brief Initialize the queue with all the possible entity IDs
                 */
                EntityManager();
                /**
                 * @brief Get an unused entity ID
                 * @return The entity ID
                 * @throw RType::Shared::Exception if there is no more entity available
                 */
                Entity createEntity();
                /**
                 * @brief Destroy an entity by adding its ID to the queue and removing its signature
                 *
                 * @param entity Entity ID
                 * @throw RType::Shared::Exception if the entity ID is invalid
                 */
                void destroyEntity(Entity entity);
                /**
                 * @brief Set the Signature for an specific entity
                 *
                 * @param entity Entity ID
                 * @param signature Signature of the entity
                 * @throw RType::Shared::Exception if the entity ID is invalid
                 */
                void setSignature(Entity entity, Signature signature);
                /**
                 * @brief Get the Signature of an entity
                 *
                 * @param entity Entity ID
                 * @return Signature of the entity
                 * @throw RType::Shared::Exception if the entity ID is invalid
                 */
                Signature getSignature(Entity entity);
                ~EntityManager();

            private:
                /**
                 * @brief Queue for unused entity IDs
                 */
                std::queue<Entity> _availableEntities;
                /**
                 * @brief Array of signatures for each entity (the index correspond to the entity ID)
                 */
                std::array<Signature, MAX_ENTITIES> _signatures;
                /**
                 * @brief Number of living entities (used to keep limits)
                 */
                ENTITY_INT_SIZE _livingEntityCount;
            };
        }
    }
}

#endif /* !__ENTITYMANAGER_HPP__ */
