/*
** EPITECH PROJECT, 2022
** RType
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            EntityManager::EntityManager()
            {
                for (ENTITY_INT_SIZE i = 0; i < MAX_ENTITIES; i++)
                    _availableEntities.push(i);
            }

            Entity EntityManager::createEntity()
            {
                if (_availableEntities.empty())
                    throw RType::Shared::Exception("No more entity available");
                Entity id = _availableEntities.front();
                _availableEntities.pop();
                _livingEntityCount++;
                return (id);
            }

            void EntityManager::destroyEntity(Entity entity)
            {
                if (entity >= MAX_ENTITIES)
                    throw RType::Shared::Exception("Invalid entity ID");
                _signatures[entity].reset();
                _availableEntities.push(entity);
                _livingEntityCount--;
            }

            void EntityManager::setSignature(Entity entity, Signature signature)
            {
                if (entity >= MAX_ENTITIES)
                    throw RType::Shared::Exception("Invalid entity ID");
                _signatures[entity] = signature;
            }

            Signature EntityManager::getSignature(Entity entity)
            {
                if (entity >= MAX_ENTITIES)
                    throw RType::Shared::Exception("Invalid entity ID");
                return (_signatures[entity]);
            }

            EntityManager::~EntityManager()
            {
            }
        }
    }
}
