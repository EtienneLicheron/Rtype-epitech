/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SpriteRenderSystem
*/

#include "SpriteRenderSystem.hpp"

void RType::Client::Scenes::SpriteRenderSystem::update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Sprite &sprite)
{
    (void)deltatime;

    try
    {
        sprite.value.setTexture(sprite.texture);
        window.draw(sprite.value);
    }
    catch (...)
    {
    }
}
