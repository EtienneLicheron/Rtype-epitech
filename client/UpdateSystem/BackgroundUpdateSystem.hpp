/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** BackgroundUpdateSystem
*/

#ifndef __BACKGROUNDUPDATESYSTEM_HPP__
#define __BACKGROUNDUPDATESYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief BackgroundUpdateSystem class to update the background
             */
            class BackgroundUpdateSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Update the background
                     *
                     * @param deltatime the deltatime
                     * @param coordinator the coordinator
                     * @param entity the entity
                     */
                    void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::RenderWindow &window);
            };
        }
    }
}

#endif /* !__BACKGROUNDUPDATESYSTEM_HPP__ */
