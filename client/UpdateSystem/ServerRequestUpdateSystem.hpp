/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ServerRequestUpdateSystem
*/

#ifndef __SERVERREQUESTUPDATESYSTEM_HPP__
#define __SERVERREQUESTUPDATESYSTEM_HPP__
#define SERVER_REQUEST_COOLDOWN 500
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief ServerRequestUpdateSystem class to update the server request
             */
            class ServerRequestUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the server request
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param lastClick the last click
                     * @param menu the menu
                     * @param mouse the mouse
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, MenuUDP &menu, sf::Vector2i mouse);
            };
        }
    }
}

#endif /* !__SERVERREQUESTUPDATESYSTEM_HPP__ */
