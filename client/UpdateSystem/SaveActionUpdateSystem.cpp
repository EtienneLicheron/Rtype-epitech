/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SaveActionUpdateSystem
*/

#include "SaveActionUpdateSystem.hpp"

void RType::Client::Scenes::SaveActionUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, sf::Vector2i mouse, ConfigurationManager &configManager)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    if (now.count() - lastClick.count() < SAVE_ACTION_SCENE_COOLDOWN)
        return;

    RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);

    // Checking hover
    if (mouse.x >= rect.value.getPosition().x && mouse.x <= rect.value.getPosition().x + rect.value.getSize().x && mouse.y >= rect.value.getPosition().y && mouse.y <= rect.value.getPosition().y + rect.value.getSize().y)
    {
        // Checking click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            lastClick = now;
            RType::Client::ECS::SaveAction &save = coordinator.getAttribute<RType::Client::ECS::SaveAction>(entity);
            RType::Client::ECS::Slider &slider_menuMusicVolume = coordinator.getAttribute<RType::Client::ECS::Slider>(save.menuMusicVolumeEntity);
            RType::Client::ECS::Slider &slider_gameMusicVolume = coordinator.getAttribute<RType::Client::ECS::Slider>(save.gameMusicVolumeEntity);
            RType::Client::ECS::Slider &slider_gameSoundVolume = coordinator.getAttribute<RType::Client::ECS::Slider>(save.gameSoundsVolumeEntity);
            configManager.setValue("menuMusicVolume", std::to_string(slider_menuMusicVolume.value));
            configManager.setValue("gameMusicVolume", std::to_string(slider_gameMusicVolume.value));
            configManager.setValue("gameSoundsVolume", std::to_string(slider_gameSoundVolume.value));
        }
    }
}
