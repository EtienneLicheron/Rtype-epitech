/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TextRenderSystem
*/

#ifndef __TEXTRENDERSYSTEM_HPP__
#define __TEXTRENDERSYSTEM_HPP__
#include "../Scenes/AScene.hpp"
#include "../Resources.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The Text Render System class
             */
            class TextRenderSystem : public RType::Shared::ECS::System
            {
                public:
                    /**
                     * @brief Construct a new Text Render System object
                     *
                     * @param deltatime the deltatime
                     * @param window the window
                     * @param text the text
                     */
                    void update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Text &text);
            };
        }
    }
}

#endif /* !__TEXTRENDERSYSTEM_HPP__ */
