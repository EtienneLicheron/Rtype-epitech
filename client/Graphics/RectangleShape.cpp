/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** RectangleShape
*/

#include "RectangleShape.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            RectangleShape::RectangleShape(::sf::Vector2f size, ::sf::Vector2f position, ::sf::Color color, float rotation, ::sf::Vector2f scale)
            {
                _rectangleShape.setScale(scale);
                _rectangleShape.setRotation(rotation);
                _rectangleShape.setFillColor(color);
                _rectangleShape.setSize(size);
                _rectangleShape.setPosition(position);
            }

            RectangleShape::RectangleShape(::sf::RectangleShape &rect, ::sf::Color color)
            {
                _rectangleShape.setScale(rect.getScale());
                _rectangleShape.setRotation(rect.getRotation());
                _rectangleShape.setFillColor(color);
                _rectangleShape.setSize(rect.getSize());
                _rectangleShape.setPosition(rect.getPosition());
            }

            sf::RectangleShape &RectangleShape::getRectangleShape()
            {
                return (_rectangleShape);
            }

            RectangleShape::~RectangleShape()
            {
            }
        }
    }
}
