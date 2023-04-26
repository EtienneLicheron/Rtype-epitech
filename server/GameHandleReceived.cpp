/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** GameHandleReceived
*/

#include "Game.hpp"

namespace RType
{
    namespace Server
    {
        void Game::handleStart(PlayerPacket cliPacket)
        {
            _player = "player_" + std::to_string(_playerId);
            cliPacket.second.setPlayerNumber(_player);
            _playerId++;
            if (_playerId > 4)
                _playerId = 1;
            RType::Shared::ECS::Entity tmp;
            tmp = _coordinator.createEntity(_player);

            _coordinator.addAttribute<RType::Server::ECS::Position>(tmp, {800.f, 50.f * _playerId});
            _coordinator.addAttribute<RType::Shared::ECS::Speed>(tmp, {10.f});
            _coordinator.addAttribute<RType::Shared::ECS::Health>(tmp, {3});

            RType::Server::ECS::Position &pos = _coordinator.getAttribute<RType::Server::ECS::Position>(tmp);

            std::string body = _player + "|" + cliPacket.second.getUsername() + "|" + std::to_string(800.f) + "|" + std::to_string(50.f * _playerId) + "|" + cliPacket.second.getUsername();
            RType::Shared::Packet packet = RType::Shared::createPacket("Spawn", body);
            _toSend.push(packet);
            std::cout << "Spawn" << body << std::endl;
            std::cout << _toSend.empty() << std::endl;
            getRoomInGame().setLocked(true);
        }

        void Game::handleDestroy(PlayerPacket cliPacket)
        {
            std::vector<std::string> body = Shared::parsePacket(cliPacket.first._body, "|");
            for (auto &entity : _coordinator.getEntities())
            {
                try
                {
                    RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                    if (entityType.value == body[0])
                    {
                        _coordinator.destroyEntity(entity);
                        break;
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }

        void Game::handleMove(PlayerPacket cliPacket)
        {
            try
            {
                std::vector<std::string> body = Shared::parsePacket(cliPacket.first._body, "|");
                for (auto &entity : _coordinator.getEntities())
                {
                    try
                    {
                        RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                        if (entityType.value == cliPacket.second.getPlayerNumber())
                        {
                            RType::Server::ECS::Position &pos = _coordinator.getAttribute<RType::Server::ECS::Position>(entity);
                            RType::Shared::ECS::Speed &speed = _coordinator.getAttribute<RType::Shared::ECS::Speed>(entity);
                            if (body[0] == "UP")
                                pos.y -= speed.value;
                            if (body[0] == "DOWN")
                                pos.y += speed.value;
                            if (body[0] == "LEFT")
                                pos.x -= speed.value;
                            if (body[0] == "RIGHT")
                                pos.x += speed.value;
                            // check if the player is out of the map
                            if (pos.x < 75)
                                pos.x = 75;
                            if (pos.x > 1600)
                                pos.x = 1600;
                            if (pos.y < 0)
                                pos.y = 0;
                            if (pos.y > 801)
                                pos.y = 801;
                            RType::Shared::Packet packet = RType::Shared::createPacket("Move", std::to_string(pos.x) + "|" + std::to_string(pos.y) + "|" + cliPacket.second.getPlayerNumber());
                            _toSend.push(packet);
                            return;
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        void Game::handleCollision(PlayerPacket cliPacket)
        {
            std::vector<std::string> body = Shared::parsePacket(cliPacket.first._body, "|");
            for (auto &entity : _coordinator.getEntities())
            {
                try
                {
                    RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                    if (entityType.value == body[0])
                    {
                        _hp--;
                        break;
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }

        void Game::handleShoot(PlayerPacket cliPacket)
        {
            for (auto &entity : _coordinator.getEntities()) {
                RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                if (entityType.value == cliPacket.second.getPlayerNumber()) {
                    // first bullet
                    RType::Shared::ECS::Entity bullet = _coordinator.createEntity("bullet_" + std::to_string(_bulletId));
                    RType::Server::ECS::Position &playerPos = _coordinator.getAttribute<RType::Server::ECS::Position>(entity);
                    _coordinator.addAttribute<RType::Server::ECS::Position>(bullet, {playerPos.x, playerPos.y});
                    RType::Shared::Packet packet = RType::Shared::createPacket("Shoot", std::to_string(_bulletId) + "|" + std::to_string(playerPos.x + 100.f) + "|" + std::to_string(playerPos.y) + "|10.f|0.f" + "|" + "1");                    _bulletId++;
                    _toSend.push(packet);
                    _bulletId++;
                    // second bullet
                    RType::Shared::ECS::Entity bullet2 = _coordinator.createEntity("bullet_" + std::to_string(_bulletId));
                    _coordinator.addAttribute<RType::Server::ECS::Position>(bullet2, {playerPos.x, playerPos.y});
                    packet = RType::Shared::createPacket("Shoot", std::to_string(_bulletId) + "|" + std::to_string(playerPos.x + 100.f) + "|" + std::to_string(playerPos.y + 90.f) + "|10.f|0.f" + "|" + "1");
                    _toSend.push(packet);
                    _bulletId++;
                }
            }
        }

        void Game::handleHit(PlayerPacket cliPacket)
        {
            std::vector<std::string> body = Shared::parsePacket(cliPacket.first._body, "|");
            try {
                for (auto &entity : _coordinator.getEntities()) {
                    RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                    if (entityType.value == body[0]) {
                        RType::Shared::ECS::Health &health = _coordinator.getAttribute<RType::Shared::ECS::Health>(entity);
                        health.value -= 1;
                        for (auto &entityBullet : _coordinator.getEntities()) {
                            RType::Shared::ECS::EntityType &bulletEntityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entityBullet);
                            if (bulletEntityType.value == body[1]) {
                                _coordinator.destroyEntity(entityBullet);
                            }
                        }
                        if (health.value <= 0) {
                            _coordinator.destroyEntity(entity);
                            RType::Shared::Packet packet = RType::Shared::createPacket("Destroy", body[0] + "|" + "1");
                            _toSend.push(packet);
                            _nbEnemies --;
                            _destroyedEnemies++;
                        }
                    }
                }
            }
            catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void Game::handleGameLoaded(PlayerPacket cliPacket)
        {
            _isGameLoaded = true;
        }
    }
}