/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Text
*/

#include "Text.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            Text::Text(std::string text, ::sf::FloatRect container, ::sf::Vector2f position, int size, ::sf::Color color)
            {
                _text.setFillColor(color);
                _text.setCharacterSize(size);
                _text.setString(text);
                _text.setPosition(container.left + (container.width * position.x), container.top + (container.height * position.y) - (size / 1.5));
            }

            Text::Text(std::string text, ::sf::Vector2f position, int size, ::sf::Color color)
            {
                _text.setFillColor(color);
                _text.setCharacterSize(size);
                _text.setString(text);
                _text.setPosition(position.x, position.y);
            }

            sf::Text Text::getText()
            {
                return (_text);
            }

            Text::~Text()
            {
            }
        }
    }
}
