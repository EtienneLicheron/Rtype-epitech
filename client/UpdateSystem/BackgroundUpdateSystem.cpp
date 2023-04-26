/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** BackgroundUpdateSystem
*/

#include "BackgroundUpdateSystem.hpp"

void RType::Client::Scenes::BackgroundUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::RenderWindow &window)
{
    RType::Client::ECS::Sprite &sprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entity);
    RType::Shared::ECS::Speed &speed = coordinator.getAttribute<RType::Shared::ECS::Speed>(entity);

    sprite.value.setTextureRect(sf::IntRect(sprite.value.getTextureRect().left + (speed.value * deltatime), 0, window.getSize().x, window.getSize().y));
}
