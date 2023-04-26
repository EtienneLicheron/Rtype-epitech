/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Text
*/

#ifndef __TEXT_HPP__
#define __TEXT_HPP__
#include <SFML/Graphics.hpp>

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief Text class to create a text
             */
            class Text
            {
                public:
                    /**
                     * @brief Construct a new Text object
                     *
                     * @param text the text to display
                     * @param container the container of the text
                     * @param position the position of the text
                     * @param size the size of the text
                     * @param color the color of the text
                     */
                    Text(std::string text, ::sf::FloatRect container = {0, 0, 0, 0}, ::sf::Vector2f position = {0.05f, 0.5f}, int size = 60, ::sf::Color color = {0, 0, 0, 255});

                    /**
                     * @brief Construct a new Text object
                     *
                     * @param text the text to display
                     * @param position the position of the text
                     * @param size the size of the text
                     * @param color the color of the text
                     */
                    Text(std::string text, ::sf::Vector2f position, int size, ::sf::Color color);

                    /**
                     * @brief Get the Text object
                     *
                     * @return sf::Text
                     */
                    sf::Text getText();
                    ~Text();

                private:
                    sf::Text _text;
            };
        }
    }
}

#endif /* !__TEXT_HPP__ */
