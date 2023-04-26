/*
** EPITECH PROJECT, 2022
** RType
** File description:
** AttributeManager
*/

#ifndef __ATTRIBUTEMANAGER_HPP__
#define __ATTRIBUTEMANAGER_HPP__
#include "Attribute.hpp"
#include "AttributeArray.hpp"
#include <memory>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief The AttributeManager class will talk to all AttributeArrays and tell them when an attribute is added or removed
             */
            class AttributeManager
            {
            public:
                /**
                 * @brief Register an attribute type
                 *
                 * @tparam T The type of the attribute
                 */
                template <typename T>
                void registerAttribute()
                {
                    const char *typeName = typeid(T).name();
                    if (_attributeTypes.find(typeName) != _attributeTypes.end())
                        throw RType::Shared::Exception("Attribute type already registered");
                    _attributeTypes.insert({typeName, _nextAttributeType});
                    _attributeArrays.insert({typeName, std::make_shared<AttributeArray<T>>()});
                    _nextAttributeType++;
                };
                /**
                 * @brief Get the AttributeType of an attribute (the id)
                 *
                 * @tparam T The type of the attribute
                 * @return AttributeType The id of the attribute
                 */
                template <typename T>
                AttributeType getAttributeType()
                {
                    const char *typeName = typeid(T).name();
                    if (_attributeTypes.find(typeName) == _attributeTypes.end())
                        throw RType::Shared::Exception("Attribute \"" + std::string(typeName) + "\" not registered before use");
                    return (_attributeTypes[typeName]);
                };
                /**
                 * @brief Check the AttributeType of an attribute (the id)
                 *
                 * @tparam T The type of the attribute
                 * @return AttributeType The id of the attribute
                 */
                template <typename T>
                bool hasAttributeType()
                {
                    const char *typeName = typeid(T).name();
                    if (_attributeTypes.find(typeName) == _attributeTypes.end())
                        return false;
                    return true;
                }
                /**
                 * @brief Add an attribute to an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to add the attribute to
                 * @param attribute The attribute to add
                 * @return T The attribute
                 */
                template <typename T>
                T &addAttribute(Entity entity, T attribute)
                {
                    getAttributeArray<T>()->insertData(entity, attribute);
                    return (getAttributeArray<T>()->getData(entity));
                };
                /**
                 * @brief Remove an attribute from an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to remove the attribute from
                 */
                template <typename T>
                void removeAttribute(Entity entity)
                {
                    getAttributeArray<T>()->removeData(entity);
                };
                /**
                 * @brief Get an attribute from an entity
                 *
                 * @tparam T The type of the attribute
                 * @param entity The entity to get the attribute from
                 * @return T The attribute
                 */
                template <typename T>
                T &getAttribute(Entity entity)
                {
                    return (getAttributeArray<T>()->getData(entity));
                };
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
                    return (getAttributeArray<T>()->hasData(entity));
                }
                /**
                 * @brief Tell all AttributeArrays that an entity has been destroyed
                 *
                 * @param entity The entity that has been destroyed
                 */
                void entityDestroyed(Entity entity)
                {
                    for (auto const &pair : _attributeArrays)
                        pair.second->entityDestroyed(entity);
                };

            private:
                /**
                 * @brief Map from type string pointer to an attribute type
                 */
                std::unordered_map<const char *, AttributeType> _attributeTypes{};
                /**
                 * @brief Map from type string pointer to an attribute array
                 */
                std::unordered_map<const char *, std::shared_ptr<IAttributeArray>> _attributeArrays{};
                /**
                 * @brief The next attribute type to be assigned /!\ it starts at 0
                 */
                AttributeType _nextAttributeType{};
                /**
                 * @brief Convenience function to get the statically casted pointer to the AttributeArray of type T.
                 */
                template <typename T>
                std::shared_ptr<AttributeArray<T>> getAttributeArray()
                {
                    const char *typeName = typeid(T).name();
                    if (_attributeTypes.find(typeName) == _attributeTypes.end())
                        throw RType::Shared::Exception("Attribute \"" + std::string(typeName) + "\" not registered before use");
                    return std::static_pointer_cast<AttributeArray<T>>(_attributeArrays[typeName]);
                };
            };
        }
    }
}

#endif /* !__ATTRIBUTEMANAGER_HPP__ */
