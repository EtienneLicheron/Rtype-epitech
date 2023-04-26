/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** GameHandleReceived
*/

#include "GameUDP.hpp"
#include "../Application.hpp"

namespace RType
{
    namespace Client
    {
        void GameUDP::handleSpawn(RType::Shared::Packet packet)
        {
            try
            {
                while (!_app.isLoaded("Game"))
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                std::vector<std::string> args = RType::Shared::parsePacket(packet._body, "|");
                if (args[1].compare(_username) == 0)
                {
                    _player = args[0];
                    _app.setPlayerID(_player);
                }
                RType::Shared::ECS::Entity _tmpEntity;
                _tmpEntity = _app.getCoordinator().createEntity(args[0]);
                _app.getCoordinator().addAttribute<RType::Client::ECS::Sprite>(_tmpEntity, {RType::Client::Graphics::Sprite({std::stof(args[2]), std::stof(args[3])}, 90.f, {1, 1}).getSprite(), RType::Client::Graphics::Texture(args[0] + ".png").getTexture()});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Text>(_tmpEntity, {{RType::Client::Graphics::Text(args[4], {std::stof(args[2]), std::stof(args[3])}, 20, {255, 255, 255, 90}).getText()}, RType::Client::Graphics::Font().getFont()});
                send(RType::Shared::createPacket("Gameloaded", ""));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        void GameUDP::handleSpawnEnemy(RType::Shared::Packet packet)
        {
            try
            {
                std::vector<std::string> args = RType::Shared::parsePacket(packet._body, "|");
                RType::Shared::ECS::Entity _tmpEntity = _app.getCoordinator().createEntity(args[0]);
                _app.getCoordinator().addAttribute<RType::Client::ECS::Sprite>(_tmpEntity, {RType::Client::Graphics::Sprite({std::stof(args[1]), std::stof(args[2])}, 90.f, {1, 1}).getSprite(), RType::Client::Graphics::Texture("enemy_" + args[3] + ".png").getTexture()});
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        void GameUDP::handleMove(RType::Shared::Packet packet)
        {
            try
            {
                std::vector<std::string> args = RType::Shared::parsePacket(packet._body, "|");
                for (auto &entity : _app.getCoordinator().getEntities())
                {
                    try
                    {
                        RType::Shared::ECS::EntityType &entityType = _app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity);
                        if (entityType.value == args[2])
                        {
                            RType::Client::ECS::Sprite &sprite = _app.getCoordinator().getAttribute<RType::Client::ECS::Sprite>(entity);
                            // sprite.value.move(std::stof(args[0]) - sprite.value.getPosition().x, std::stof(args[1]) - sprite.value.getPosition().y);
                            sprite.value.setPosition(std::stof(args[0]), std::stof(args[1]));
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        void GameUDP::handleShoot(RType::Shared::Packet packet)
        {
            std::vector<std::string> args = RType::Shared::parsePacket(packet._body, "|");
            RType::Shared::ECS::Entity tmpEntity = _app.getCoordinator().createEntity("bullet_" + args[0]);
            if (args[5].compare("1") == 0)
                _app.getCoordinator().addAttribute<RType::Client::ECS::Sprite>(tmpEntity, {RType::Client::Graphics::Sprite({std::stof(args[1]), std::stof(args[2])}, 90.f, {1, 1}).getSprite(), RType::Client::Graphics::Texture("laser" + args[5] + ".png").getTexture()});
            else
                _app.getCoordinator().addAttribute<RType::Client::ECS::Sprite>(tmpEntity, {RType::Client::Graphics::Sprite({std::stof(args[1]), std::stof(args[2])}, -90.f, {1, 1}).getSprite(), RType::Client::Graphics::Texture("laser" + args[5] + ".png").getTexture()});
            _app.getCoordinator().addAttribute<RType::Shared::ECS::Velocity>(tmpEntity, {std::stof(args[3]), std::stof(args[4])});
            for (auto &entity : _app.getCoordinator().getEntities()) {
                RType::Shared::ECS::EntityType &entityType = _app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity);
                if (entityType.value == "laserShoot") {
                    RType::Client::ECS::Sound &sound = _app.getCoordinator().getAttribute<RType::Client::ECS::Sound>(entity);
                    sound.playing = true;
                }
            }
        }

        void GameUDP::handleDestroy(RType::Shared::Packet packet)
        {
            try
            {
                std::vector<std::string> args = RType::Shared::parsePacket(packet._body, "|");
                for (auto &entity : _app.getCoordinator().getEntities())
                {
                    try
                    {
                        RType::Shared::ECS::EntityType &entityType = _app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity);
                        if (entityType.value == args[0])
                        {
                            if (entityType.value.find("enemy_") != std::string::npos || entityType.value.find("player_") != std::string::npos) {
                                for (auto &entitySound : _app.getCoordinator().getEntities()) {
                                    RType::Shared::ECS::EntityType &entityType = _app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entitySound);
                                    if (entityType.value == "enemyDestroyed" && args[1] == "1") {
                                        RType::Client::ECS::Sound &sound = _app.getCoordinator().getAttribute<RType::Client::ECS::Sound>(entitySound);
                                        sound.playing = true;
                                    }
                                }
                            }
                            _app.getCoordinator().destroyEntity(entity);
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}
