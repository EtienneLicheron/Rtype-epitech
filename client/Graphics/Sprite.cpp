/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Sprite
*/

#include "Sprite.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            Sprite::Sprite(::sf::Vector2f position, float rotation, ::sf::Vector2f scale)
            {
                _sprite.setScale(scale);
                _sprite.setRotation(rotation);
                _sprite.setPosition(position);
            }

            sf::Sprite &Sprite::getSprite()
            {
                return _sprite;
            }

            Sprite::~Sprite()
            {
            }
        }
    }
}
