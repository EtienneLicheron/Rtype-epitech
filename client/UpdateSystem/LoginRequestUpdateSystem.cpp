/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** LoginRequestUpdateSystem
*/

#include "LoginRequestUpdateSystem.hpp"

void RType::Client::Scenes::LoginRequestUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, sf::Vector2i mouse, MenuUDP &menu, ConfigurationManager &configManager)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    if (now.count() - lastClick.count() < LOGIN_REQUEST_SCENE_COOLDOWN)
        return;

    RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);

    // Checking hover
    if (mouse.x >= rect.value.getPosition().x && mouse.x <= rect.value.getPosition().x + rect.value.getSize().x && mouse.y >= rect.value.getPosition().y && mouse.y <= rect.value.getPosition().y + rect.value.getSize().y)
    {
        // Checking click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            lastClick = now;

            RType::Client::ECS::LoginRequest &login = coordinator.getAttribute<RType::Client::ECS::LoginRequest>(entity);

            std::string usernameString = coordinator.getAttribute<RType::Client::ECS::InputString>(login.username).text.value.getString();
            std::string addressString = coordinator.getAttribute<RType::Client::ECS::InputString>(login.address).text.value.getString();
            std::string portString = coordinator.getAttribute<RType::Client::ECS::InputString>(login.port).text.value.getString();

            configManager.setValue("username", usernameString);
            configManager.setValue("address", addressString);
            configManager.setValue("port", portString);

            std::stringstream ss;
            unsigned short port;

            ss << portString;
            ss >> port;

            // Reset UDP and Send login request
            menu.reset(addressString, port, usernameString);
        }
    }
}
