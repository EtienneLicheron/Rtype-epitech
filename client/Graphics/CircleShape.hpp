/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** CircleShape
*/

#ifndef __CIRCLESHAPE_HPP__
#define __CIRCLESHAPE_HPP__
#include <SFML/Graphics.hpp>

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief CircleShape class to create a circle
             */
            class CircleShape
            {
                public:
                    /**
                     * @brief constructor of the CircleShape class
                     * @param position the position of the circle
                     * @param radius the radius of the circle
                     * @param scale scale of the circle
                     * @param color color of the circle
                     */
                    CircleShape(::sf::Vector2f position, float radius, ::sf::Vector2f scale, ::sf::Color color);

                    /**
                     * @brief Get the Circle Shape object
                     *
                     * @return ::sf::CircleShape&
                     */
                    ::sf::CircleShape &getCircleShape();
                    ~CircleShape();

                private:
                    ::sf::CircleShape _circleShape;
            };
        }
    }
}

#endif /* !__CIRCLESHAPE_HPP__ */
