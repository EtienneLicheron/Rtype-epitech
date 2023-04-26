/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** RectangleShape
*/

#ifndef __RECTANGLESHAPE_HPP__
#define __RECTANGLESHAPE_HPP__
#include <SFML/Graphics.hpp>

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief RectangleShape class to create a rectangle
             */
            class RectangleShape
            {
                public:
                    /**
                     * @brief Construct a new Rectangle Shape object
                     *
                     * @param size the size of the rectangle
                     * @param position the position of the rectangle
                     * @param color the color of the rectangle
                     * @param rotation the rotation of the rectangle
                     * @param scale the scale of the rectangle
                     */
                    RectangleShape(::sf::Vector2f size, ::sf::Vector2f position = {0.f, 0.f}, ::sf::Color color = {255, 255, 255, 255}, float rotation = 0.f, ::sf::Vector2f scale = {1.f, 1.f});

                    /**
                     * @brief Construct a new Rectangle Shape object
                     *
                     * @param rect the rectangle
                     * @param color the color of the rectangle
                     */
                    RectangleShape(::sf::RectangleShape &rect, ::sf::Color color);
                    ::sf::RectangleShape &getRectangleShape();
                    ~RectangleShape();

                private:
                    ::sf::RectangleShape _rectangleShape;
            };
        }
    }
}

#endif /* !__RECTANGLESHAPE_HPP__ */
