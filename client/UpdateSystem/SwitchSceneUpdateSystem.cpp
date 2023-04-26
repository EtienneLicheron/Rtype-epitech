/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SwitchSceneUpdateSystem
*/

#include "SwitchSceneUpdateSystem.hpp"

void RType::Client::Scenes::SwitchSceneUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, std::string &currentScene, sf::Vector2i mouse)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    if (now.count() - lastClick.count() < SWITCH_SCENE_COOLDOWN)
        return;

    RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);
    RType::Client::ECS::SwitchScene &switchScene = coordinator.getAttribute<RType::Client::ECS::SwitchScene>(entity);

    // Checking hover
    if (mouse.x >= rect.value.getPosition().x && mouse.x <= rect.value.getPosition().x + rect.value.getSize().x && mouse.y >= rect.value.getPosition().y && mouse.y <= rect.value.getPosition().y + rect.value.getSize().y)
    {
        // Checking click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            lastClick = now;

            // Switch scene
            currentScene = switchScene.value;
        }
    }
}
