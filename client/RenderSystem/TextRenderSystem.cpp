/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TextRenderSystem
*/

#include "TextRenderSystem.hpp"

void RType::Client::Scenes::TextRenderSystem::update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Text &text)
{
    (void)deltatime;

    try
    {
        text.value.setFont(text.font);
        window.draw(text.value);
    }
    catch (...)
    {
    }
}
