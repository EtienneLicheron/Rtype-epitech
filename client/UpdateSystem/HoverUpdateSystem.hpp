/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** HoverUpdateSystem
*/

#ifndef __HOVERUPDATESYSTEM_HPP__
#define __HOVERUPDATESYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief HoverUpdateSystem class to update the hover
             */
            class HoverUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the hover
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param mouse the mouse
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::Vector2i mouse);
            };
        }
    }
}

#endif /* !__HOVERUPDATESYSTEM_HPP__ */
