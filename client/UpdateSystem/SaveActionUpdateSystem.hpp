/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** SaveActionUpdateSystem
*/

#ifndef __SAVEACTIONUPDATESYSTEM_HPP__
#define __SAVEACTIONUPDATESYSTEM_HPP__
#define SAVE_ACTION_SCENE_COOLDOWN 250
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief SaveActionUpdateSystem class to update the save action
             */
            class SaveActionUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the save action
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param event the event
                     * @param menu the menu
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, sf::Vector2i mouse, ConfigurationManager &configManager);
            };
        }
    }
}

#endif /* !__SAVEACTIONUPDATESYSTEM_HPP__ */
