/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** PlayerUpdateSystem
*/

#include "PlayerUpdateSystem.hpp"

void RType::Client::Scenes::PlayerUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::Event &event, MenuUDP &menu)
{
    static std::chrono::milliseconds lastRequest = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    RType::Client::ECS::Sprite &sprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entity);
    RType::Shared::ECS::EntityType &entityPlayerType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);

    for (auto &entity : coordinator.getEntities())
    {
        try {
            RType::Shared::ECS::EntityType &entityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
            if (entityType.value.find("enemy_") != std::string::npos) {
                RType::Client::ECS::Sprite &enemySprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entity);
                if (sprite.value.getGlobalBounds().intersects(enemySprite.value.getGlobalBounds())) {
                    std::cout << "HIThere" << std::endl;
                    menu.getGame()->send(RType::Shared::createPacket("Collision", entityPlayerType.value));
                    continue;
                }
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    if (event.type == event.KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            menu.getGame()->send(RType::Shared::createPacket("Move", "UP"));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            menu.getGame()->send(RType::Shared::createPacket("Move", "LEFT"));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            menu.getGame()->send(RType::Shared::createPacket("Move", "DOWN"));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            menu.getGame()->send(RType::Shared::createPacket("Move", "RIGHT"));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (now.count() - lastRequest.count() < 500)
                return;
            menu.getGame()->send(RType::Shared::createPacket("Shoot", "BASIC"));
            lastRequest = now;
        }
    }
}
