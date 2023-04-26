/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SwitchSceneUpdateSystem
*/

#ifndef __SWITCHSCENEUPDATESYSTEM_HPP__
#define __SWITCHSCENEUPDATESYSTEM_HPP__
#define SWITCH_SCENE_COOLDOWN 250
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief SwitchSceneUpdateSystem class to update the switch scene
             */
            class SwitchSceneUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the switch scene
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param lastClick the last click
                     * @param menu the menu
                     * @param mouse the mouse
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, std::string &currentScene, sf::Vector2i mouse);
            };
        }
    }
}

#endif /* !__SWITCHSCENEUPDATESYSTEM_HPP__ */
