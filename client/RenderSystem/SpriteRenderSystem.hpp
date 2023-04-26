/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpriteRenderSystem
*/

#ifndef __SPRITERENDERSYSTEM_HPP__
#define __SPRITERENDERSYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The Sprite Render System class
             */
            class SpriteRenderSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Construct a new Sprite Render System object
                     *
                     * @param deltatime the deltatime
                     * @param window the window
                     * @param sprite the sprite
                     */
                    void update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Sprite &sprite);
            };
        }
    }
}

#endif /* !__SPRITERENDERSYSTEM_HPP__ */
