/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Coordinator
*/

#ifndef __COORDINATOR_HPP__
#define __COORDINATOR_HPP__
#include "AttributeManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include <memory>
#include <thread>
#include <iostream>
#include <mutex>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The coordinator is the main class of the ECS, it will handle all the entities, components and systems
             */
            class Coordinator
            {
            public:
                /**
                 * @brief The constructor actually does nothing, you MUST call init() after the creation of the coordinator to properly use it
                 */
                Coordinator();
                ~Coordinator();

                Coordinator &operator=(const Coordinator &coordinator);
                /**
                 * @brief Initialize all managers for us
                 */
                void init();
                ////// ENTITIES METHODS //////
                /**
                 * @brief Create a new entity
                 * @param entity The entity type
                 * @return The new entity
                 */
                Entity createEntity(std::string entityType);
                /**
                 * @brief Destroy an entity
                 * @param entity The entity to destroy
                 */
                void destroyEntity(Entity entity);
                ////// ATTRIBUTES METHODS //////
                /**
                 * @brief Register an attribute
                 *
                 * @tparam T The type of the attribute
                 */
                template <typename T>
                void registerAttribute()
                {
                    _attributeManager.get()->registerAttribute<T>();
                }
                /**
                 * @brief Add an attribute to an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to add the attribute to
                 * @param attribute The attribute to add
                 * @return The attribute
                 */
                template <typename T>
                T &addAttribute(Entity entity, T attribute)
                {
                    return _attributeManager.get()->addAttribute<T>(entity, attribute);
                }
                /**
                 * @brief Remove an attribute from an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to remove the attribute from
                 */
                template <typename T>
                void removeAttribute(Entity entity)
                {
                    _attributeManager.get()->removeAttribute<T>(entity);
                }
                /**
                 * @brief Get an attribute from an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to get the attribute from
                 * @return The attribute
                 */
                template <typename T>
                T &getAttribute(Entity entity)
                {
                    return (_attributeManager.get()->getAttribute<T>(entity));
                }
                /**
                 * @brief Check an attribute from an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to get the attribute from
                 * @return boolean
                 */
                template <typename T>
                bool hasAttribute(Entity entity)
                {
                    return (_attributeManager.get()->hasAttribute<T>(entity));
                }
                /**
                 * @brief Get the Attribute Type of an entity
                 *
                 * @tparam T The type of the attribute
                 * @return AttributeType The attribute type
                 */
                template <typename T>
                AttributeType getAttributeType()
                {
                    return (_attributeManager->getAttributeType<T>());
                }
                /**
                 * @brief Check the Attribute Type of an entity
                 *
                 * @tparam T The type of the attribute
                 * @return boolean
                 */
                template <typename T>
                bool hasAttributeType()
                {
                    return (_attributeManager->hasAttributeType<T>());
                }
                ////// SYSTEMS METHODS //////
                /**
                 * @brief Register a system
                 *
                 * @tparam T The type of the system
                 */
                template <typename T>
                std::shared_ptr<T> registerSystem()
                {
                    return (_systemManager->registerSystem<T>());
                }
                /**
                 * @brief Set the signature of a system
                 *
                 * @tparam T The type of the system
                 * @param signature The signature of the system
                 */
                template <typename T>
                void setSystemSignature(Signature signature)
                {
                    _systemManager->setSignature<T>(signature);
                }
                /**
                 * @brief Get the Entities ID
                 *
                 * @return std::vector<Entity> All entities
                 */
                std::vector<Entity> getEntities() const;

            private:
                std::unique_ptr<AttributeManager> _attributeManager;
                std::unique_ptr<EntityManager> _entityManager;
                std::unique_ptr<SystemManager> _systemManager;
                std::vector<RType::Shared::ECS::Entity> _entities;
            };
        }
    }
}

#endif /* !__COORDINATOR_HPP__ */
