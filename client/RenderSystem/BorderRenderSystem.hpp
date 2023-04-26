/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BorderRenderSystem
*/

#ifndef __BORDERRENDERSYSTEM_HPP__
#define __BORDERRENDERSYSTEM_HPP__
#include "../Scenes/AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The Border Render System class
             */
            class BorderRenderSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Construct a new Border Render System object
                     *
                     * @param deltatime the deltatime
                     * @param window the window
                     * @param border the border
                     * @param position the position
                     * @param size the size
                     */
                    void update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Border &border, const ::sf::Vector2f position, const ::sf::Vector2f size);

                private:
                    ::sf::RectangleShape _tmpRect;
            };
        }
    }
}

#endif /* !__BORDERRENDERSYSTEM_HPP__ */
