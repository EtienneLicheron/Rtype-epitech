/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InputStringUpdateSystem
*/

#ifndef __INPUTSTRINGUPDATESYSTEM_HPP__
#define __INPUTSTRINGUPDATESYSTEM_HPP__
#define INPUT_STRING_COOLDOWN 125
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief InputStringUpdateSystem class to update the input string
             */
            class InputStringUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the input string
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param window the window
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, ::sf::Event &event, sf::Vector2i mouse);
            };
        }
    }
}

#endif /* !__INPUTSTRINGUPDATESYSTEM_HPP__ */
