/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** PlayerUpdateSystem
*/

#ifndef __PLAYERUPDATESYSTEM_HPP__
#define __PLAYERUPDATESYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief PlayerUpdateSystem class to update the player
             */
            class PlayerUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the player
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     * @param event the event
                     * @param menu the menu
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::Event &event, MenuUDP &menu);
            };
        }
    }
}

#endif /* !__PLAYERUPDATESYSTEM_HPP__ */
