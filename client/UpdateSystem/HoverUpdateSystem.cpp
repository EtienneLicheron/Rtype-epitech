/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** HoverUpdateSystem
*/

#include "HoverUpdateSystem.hpp"

void RType::Client::Scenes::HoverUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::Vector2i mouse)
{
    RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);
    RType::Client::ECS::Hover &hover = coordinator.getAttribute<RType::Client::ECS::Hover>(entity);

    // Checking hover
    if (mouse.x >= rect.value.getPosition().x && mouse.x <= rect.value.getPosition().x + rect.value.getSize().x && mouse.y >= rect.value.getPosition().y && mouse.y <= rect.value.getPosition().y + rect.value.getSize().y)
    {
        if (hover.rect.value.getFillColor().a + (hover.transition * deltatime) >= 255)
            hover.rect.value.setFillColor({hover.rect.value.getFillColor().r, hover.rect.value.getFillColor().g, hover.rect.value.getFillColor().b, 255});
        else
            hover.rect.value.setFillColor({hover.rect.value.getFillColor().r, hover.rect.value.getFillColor().g, hover.rect.value.getFillColor().b, static_cast<unsigned char>(hover.rect.value.getFillColor().a + hover.transition * deltatime)});
    }
    else
    {
        if (hover.rect.value.getFillColor().a - (hover.transition * deltatime) <= 0)
            hover.rect.value.setFillColor({hover.rect.value.getFillColor().r, hover.rect.value.getFillColor().g, hover.rect.value.getFillColor().b, 0});
        else
            hover.rect.value.setFillColor({hover.rect.value.getFillColor().r, hover.rect.value.getFillColor().g, hover.rect.value.getFillColor().b, static_cast<unsigned char>(hover.rect.value.getFillColor().a - hover.transition * deltatime)});
    }
}
