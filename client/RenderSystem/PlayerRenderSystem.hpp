/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** PlayerRenderSystem
*/

#ifndef __PLAYERRENDERSYSTEM_HPP__
#define __PLAYERRENDERSYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief PlayerRenderSystem class to render the player
             */
            class PlayerRenderSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Construct a new Player Render System object
                     *
                     * @param deltatime the deltatime of the game
                     * @param window the window
                     * @param sprite the sprite
                     * @param text the text
                     */
                    void update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Sprite &sprite, RType::Client::ECS::Text &text);
            };
        }
    }
}

#endif /* !__PLAYERRENDERSYSTEM_HPP__ */
