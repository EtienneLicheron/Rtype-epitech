/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** ProjectileUpdateSystem
*/

#include "ProjectileUpdateSystem.hpp"

void RType::Client::Scenes::ProjectileUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, sf::RenderWindow &window, MenuUDP &menu)
{
    RType::Client::ECS::Sprite &sprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entity);
    RType::Shared::ECS::Velocity &velocity = coordinator.getAttribute<RType::Shared::ECS::Velocity>(entity);
    RType::Shared::ECS::EntityType &bulletEntityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
    for (auto &entityHit : coordinator.getEntities())
    {
        try {
            RType::Shared::ECS::EntityType &entityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entityHit);
            if (entityType.value.find("enemy_") != std::string::npos || entityType.value.find("player_") != std::string::npos) {
                RType::Client::ECS::Sprite &enemySprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entityHit);
                if (sprite.value.getGlobalBounds().intersects(enemySprite.value.getGlobalBounds())) {
                    std::cout << "Debug : Collision" << std::endl;
                    menu.getGame()->send(RType::Shared::createPacket("Hit", entityType.value + "|" + bulletEntityType.value));
                    coordinator.destroyEntity(entity);
                    continue;
                }
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    sprite.value.move(velocity.x, velocity.y);
    if (sprite.value.getPosition().x > 2500.f || sprite.value.getPosition().x < 0 || sprite.value.getPosition().y > window.getSize().y + sprite.value.getGlobalBounds().height || sprite.value.getPosition().y < 0) {        menu.getGame()->send(RType::Shared::createPacket("Destroy", bulletEntityType.value));
        menu.getGame()->send(RType::Shared::createPacket("Destroy", bulletEntityType.value));
        coordinator.destroyEntity(entity);
    }
}
