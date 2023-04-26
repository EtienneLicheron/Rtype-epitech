/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** ProjectileUpdateSystem
*/

#ifndef __PROJECTILEUPDATESYSTEM_HPP__
#define __PROJECTILEUPDATESYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief ProjectileUpdateSystem class to update the projectile
             */
            class ProjectileUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the projectile
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::RenderWindow &window, MenuUDP &menu);
            };
        }
    }
}

#endif /* !__PROJECTILEUPDATESYSTEM_HPP__ */
