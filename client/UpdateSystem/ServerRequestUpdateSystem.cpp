/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ServerRequestUpdateSystem
*/

#include "ServerRequestUpdateSystem.hpp"

void RType::Client::Scenes::ServerRequestUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, std::chrono::milliseconds &lastClick, MenuUDP &menu, sf::Vector2i mouse)
{
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    if (now.count() - lastClick.count() < SERVER_REQUEST_COOLDOWN)
        return;

    RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);
    RType::Client::ECS::ServerRequest &req = coordinator.getAttribute<RType::Client::ECS::ServerRequest>(entity);

    if (coordinator.hasAttributeType<RType::Client::ECS::InputString>() && coordinator.hasAttribute<RType::Client::ECS::InputString>(req.link))
        req.body = coordinator.getAttribute<RType::Client::ECS::InputString>(req.link).text.value.getString();

    // Checking hover
    if (mouse.x >= rect.value.getPosition().x && mouse.x <= rect.value.getPosition().x + rect.value.getSize().x && mouse.y >= rect.value.getPosition().y && mouse.y <= rect.value.getPosition().y + rect.value.getSize().y)
    {
        // Checking click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            lastClick = now;

            printf("Server request %s %s\n", req.type.c_str(), req.body.c_str());

            // Server Request
            if (req.type.compare("CreateRoom") == 0 && req.body.size() > 0)
                menu.sendNewRoom(req.body);
            else if (req.type.compare("RoomList") == 0)
                menu.sendRoomList();
            else if (req.type.compare("LeaveRoom") == 0)
                menu.sendLeaveRoom();
            else if (req.type.compare("JoinRoom") == 0)
                menu.sendJoinRoom(req.body);
            else if (req.type.compare("Ready") == 0)
                menu.sendPlayerReady();
        }
    }
}
