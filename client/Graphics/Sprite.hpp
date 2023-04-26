/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Sprite
*/

#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__
#include <SFML/Graphics.hpp>
#include "Texture.hpp"
#include "Utils.hpp"
#include "ECS/Attribute.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief Sprite class to create a sprite
             */
            class Sprite
            {
                public:
                    /**
                     * @brief Construct a new Sprite object
                     *
                     * @param position the position of the sprite
                     * @param rotation the rotation of the sprite
                     * @param scale the scale of the sprite
                     */
                    Sprite(::sf::Vector2f position = {0.f, 0.f}, float rotation = 0.f, ::sf::Vector2f scale = {1.f, 1.f});
                    sf::Sprite &getSprite();
                    ~Sprite();

                private:
                    sf::Sprite _sprite;
            };
        }
    }
}

#endif /* !__SPRITE_HPP__ */
