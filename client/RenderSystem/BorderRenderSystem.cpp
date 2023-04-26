/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** BorderRenderSystem
*/

#include "BorderRenderSystem.hpp"

void RType::Client::Scenes::BorderRenderSystem::update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Border &border, const ::sf::Vector2f position, const ::sf::Vector2f size)
{
    (void)deltatime;

    try
    {
        _tmpRect.setSize({size.x, border.size});
        _tmpRect.setFillColor(border.color);

        if (border.top)
        {
            _tmpRect.setPosition(position.x, position.y);
            window.draw(_tmpRect);
        }

        if (border.bottom)
        {
            _tmpRect.setPosition(position.x, position.y + size.y - border.size);
            window.draw(_tmpRect);
        }

        _tmpRect.setSize({border.size, size.y});

        if (border.left)
        {
            _tmpRect.setPosition(position.x, position.y);
            window.draw(_tmpRect);
        }

        if (border.right)
        {
            _tmpRect.setPosition(position.x + size.x - border.size, position.y);
            window.draw(_tmpRect);
        }
    }
    catch (...)
    {
    }
}
