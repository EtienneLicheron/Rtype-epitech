/*
** EPITECH PROJECT, 2022
** RType
** File description:
** AttributeArray
*/

#ifndef __ATTRIBUTEARRAY_HPP__
#define __ATTRIBUTEARRAY_HPP__
#include "../Exception.hpp"
#include "IAttributeArray.hpp"
#include <array>
#include <unordered_map>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief Array that stores all the attributes of a specific type for all entities
             *
             * @tparam T Attribute type
             */
            template <typename T>
            class AttributeArray : public IAttributeArray
            {
            public:
                /**
                 * @brief Assigns an attribute to an entity
                 *
                 * @param entity Entity to assign the component to
                 * @param component Component to assign
                 */
                void insertData(Entity entity, T attribute)
                {
                    if (_entityToIndexMap.find(entity) != _entityToIndexMap.end())
                        throw RType::Shared::Exception("Attribute \"" + std::string(typeid(T).name()) + "\" already assigned to entity");
                    // Put new entry at end and update the maps
                    size_t newIndex = _size;
                    _entityToIndexMap[entity] = newIndex;
                    _indexToEntityMap[newIndex] = entity;
                    _attributesArray[newIndex] = attribute;
                    _size++;
                };
                /**
                 * @brief Removes an entity's attribute
                 *
                 * @param entity
                 */
                void removeData(Entity entity)
                {
                    if (_entityToIndexMap.find(entity) == _entityToIndexMap.end())
                        throw RType::Shared::Exception("Removing non-existent attribute");
                    // Copy element at end into deleted element's place to maintain density
                    size_t indexOfRemovedEntity = _entityToIndexMap[entity];
                    size_t indexOfLastElement = _size - 1;
                    _attributesArray[indexOfRemovedEntity] = _attributesArray[indexOfLastElement];
                    // Update map to point to moved spot
                    Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
                    _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
                    _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
                    // Remove the entry that was moved from the end
                    _entityToIndexMap.erase(entity);
                    _indexToEntityMap.erase(indexOfLastElement);
                    _size--;
                };
                /**
                 * @brief Get the attribute of an entity
                 *
                 * @param entity the entity to get the attribute from
                 * @return T& the attribute reference
                 */
                T &getData(Entity entity)
                {
                    if (_entityToIndexMap.find(entity) == _entityToIndexMap.end())
                        throw RType::Shared::Exception("Attribute \"" + std::string(typeid(T).name()) + "\" not assigned to entity");
                    return _attributesArray[_entityToIndexMap[entity]];
                };
                /**
                 * @brief Check if the entity has the attribute
                 *
                 * @param entity the entity to get the attribute from
                 * @return boolean
                 */
                bool hasData(Entity entity)
                {
                    return _entityToIndexMap.find(entity) == _entityToIndexMap.end() ? false : true;
                };
                /**
                 * @brief Destroy an entity's attribute
                 *
                 * @param entity the entity to destroy the attribute from
                 */
                void entityDestroyed(Entity entity) override
                {
                    if (_entityToIndexMap.find(entity) != _entityToIndexMap.end())
                        removeData(entity);
                };

            private:
                /**
                 * @brief Packed array of components (of type T) <br />
                 * The size of the array is the maximum number of entities that can exist at the same time <br />
                 * so each entity has a unique index in the array
                 */
                std::array<T, MAX_ENTITIES> _attributesArray;
                /**
                 * @brief Maps an entity to an index in the array
                 */
                std::unordered_map<Entity, size_t> _entityToIndexMap;
                /**
                 * @brief Maps an index in the array to an entity
                 */
                std::unordered_map<size_t, Entity> _indexToEntityMap;
                /**
                 * @brief Size of valid entry in the array
                 */
                std::size_t _size;
            };
        }
    }
}

#endif /* !__ATTRIBUTEARRAY_HPP__ */
