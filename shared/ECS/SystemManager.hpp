/*
** EPITECH PROJECT, 2022
** RType
** File description:
** SystemManager
*/

#ifndef __SYSTEMMANAGER_HPP__
#define __SYSTEMMANAGER_HPP__
#include "System.hpp"

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The system manager is the class which manage all the systems and their signatures.
             */
            class SystemManager
            {
            public:
                /**
                 * @brief Register a system
                 *
                 * @tparam T The type of the system
                 * @return std::shared_ptr<T> The pointer to the system
                 */
                template <typename T>
                std::shared_ptr<T> registerSystem()
                {
                    const char *typeName = typeid(T).name();
                    if (_systems.find(typeName) != _systems.end())
                        throw RType::Shared::Exception("System already registered");
                    std::shared_ptr<T> system = std::make_shared<T>();
                    _systems.insert({typeName, system});
                    return (system);
                };
                /**
                 * @brief Set the signature of a system
                 *
                 * @tparam T The type of the system
                 * @param signature The signature of the system
                 */
                template <typename T>
                void setSignature(Signature signature)
                {
                    const char *typeName = typeid(T).name();
                    if (_systems.find(typeName) == _systems.end())
                        throw RType::Shared::Exception("System used before registered");
                    _signatures.insert({typeName, signature});
                };
                /**
                 * @brief Get the signature of a system
                 *
                 * @tparam T The type of the system
                 * @return Signature The signature of the system
                 */
                template <typename T>
                Signature getSignature()
                {
                    const char *typeName = typeid(T).name();
                    if (_systems.find(typeName) == _systems.end())
                        throw RType::Shared::Exception("System used before registered");
                    return (_signatures[typeName]);
                };
                /**
                 * @brief Destroy an entity and remove it from all the systems
                 *
                 * @param entity The entity to destroy
                 */
                void entityDestroyed(Entity entity)
                {
                    for (auto const &pair : _systems)
                    {
                        auto const &system = pair.second;
                        system->entities.erase(entity); // it's a set so we don't need to check anything ! :)
                    }
                };
                /**
                 * @brief Notify the system manager that an entity's signature changed
                 *
                 * @param entity The entity which changed
                 * @param entitySignature The new signature of the entity
                 */
                void entitySignatureChanged(Entity entity, Signature entitySignature)
                {
                    for (auto const &pair : _systems)
                    {
                        auto const &type = pair.first;
                        auto const &system = pair.second;
                        auto const &systemSignature = _signatures[type];
                        if ((entitySignature & systemSignature) == systemSignature)
                            system->entities.insert(entity); // Entity signature matches system signature - insert into set
                        else
                            system->entities.erase(entity); // Entity signature does not match system signature - erase from set
                    }
                };

            private:
                /**
                 * @brief Map from system type string pointer to a signature
                 */
                std::unordered_map<const char *, Signature> _signatures{};
                /**
                 * @brief Map from system type string pointer to a system pointer
                 */
                std::unordered_map<const char *, std::shared_ptr<System>> _systems{};
            };
        }
    }
}

#endif /* !__SYSTEMMANAGER_HPP__ */
