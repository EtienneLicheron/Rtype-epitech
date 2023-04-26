/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** LoginRequestUpdateSystem
*/

#ifndef __LOGINREQUESTUPDATESYSTEM_HPP__
#define __LOGINREQUESTUPDATESYSTEM_HPP__
#define LOGIN_REQUEST_SCENE_COOLDOWN 250
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief LoginRequestUpdateSystem class to update the login request
             */
            class LoginRequestUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the login request
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, sf::Vector2i mouse, MenuUDP &menu, ConfigurationManager &configManager);
            };
        }
    }
}

#endif /* !__LOGINREQUESTUPDATESYSTEM_HPP__ */
