/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** CircleShape
*/

#include "CircleShape.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            CircleShape::CircleShape(::sf::Vector2f position, float radius, ::sf::Vector2f scale, ::sf::Color color)
            {
                _circleShape.setPosition(position);
                _circleShape.setRadius(radius);
                _circleShape.setScale(scale);
                _circleShape.setFillColor(color);
            }

            sf::CircleShape &CircleShape::getCircleShape()
            {
                return (_circleShape);
            }

            CircleShape::~CircleShape()
            {
            }
        }
    }
}
