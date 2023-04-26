/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            std::mutex _coordMutex;
            Coordinator::Coordinator()
            {
            }

            Coordinator::~Coordinator()
            {
            }

            Coordinator &Coordinator::operator=(const Coordinator &coordinator)
            {
                std::lock_guard<std::mutex> guard(_coordMutex);
                return *this;
            }

            void Coordinator::init()
            {
                std::lock_guard<std::mutex> guard(_coordMutex);
                std::cout << "TEST -----------------1" << std::endl;
                _attributeManager = std::make_unique<AttributeManager>();
                std::cout << "TEST -----------------2" <<std::endl;
                _entityManager = std::make_unique<EntityManager>();
                _systemManager = std::make_unique<SystemManager>();
                _attributeManager.get()->registerAttribute<RType::Shared::ECS::EntityType>();
            }

            Entity Coordinator::createEntity(std::string entityType)
            {
                std::lock_guard<std::mutex> guard(_coordMutex);
                Entity newEntity = _entityManager->createEntity();

                _entities.push_back(newEntity);
                _attributeManager.get()->addAttribute<RType::Shared::ECS::EntityType>(newEntity, {entityType});
                return (newEntity);
            }

            void Coordinator::destroyEntity(Entity entity)
            {
                std::lock_guard<std::mutex> guard(_coordMutex);
                _entityManager->destroyEntity(entity);
                _attributeManager->entityDestroyed(entity);
                _systemManager->entityDestroyed(entity);
                for (auto it = _entities.begin(); it != _entities.end(); it++)
                    if (*it == entity)
                    {
                        _entities.erase(it);
                        break;
                    }
            }

            std::vector<Entity> Coordinator::getEntities() const
            {
                std::lock_guard<std::mutex> guard(_coordMutex);
                return (_entities);
            }
        }
    }
}
