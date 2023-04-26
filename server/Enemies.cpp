/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Enemies
*/

#include "Game.hpp"

namespace RType
{
    namespace Server
    {
        void Game::createEnemy(RType::Server::ECS::Position pos)
        {
            RType::Shared::ECS::Entity entity =  _coordinator.createEntity("enemy_" + std::to_string(_enemyId));
            _coordinator.addAttribute<RType::Server::ECS::Position>(entity, {pos.x, pos.y});
            _coordinator.addAttribute<RType::Shared::ECS::Velocity>(entity, {-10.f * std::stof(_enemiesMap[_wave][4]), 0.f});
            _coordinator.addAttribute<RType::Shared::ECS::Health>(entity, {std::stoi(_enemiesMap[_wave][1])});
            _coordinator.addAttribute<RType::Shared::ECS::Clock>(entity, {std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()), std::stof(_enemiesMap[_wave][3])});
            RType::Shared::Packet packet = RType::Shared::createPacket("SpawnEnemy", "enemy_" + std::to_string(_enemyId) + "|" + std::to_string(pos.x) + "|" + std::to_string(pos.y) + "|" + _enemiesMap[_wave][0]);
            _toSend.push(packet);
            _enemyId++;
        }

        void Game::updateEnemies(void)
        {
            std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
            for (auto &entity : _coordinator.getEntities())
            {
                try
                {
                    RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                    if (entityType.value.find("enemy_") != std::string::npos)
                    {
                        RType::Server::ECS::Position &pos = _coordinator.getAttribute<RType::Server::ECS::Position>(entity);
                        RType::Shared::ECS::Velocity &vel = _coordinator.getAttribute<RType::Shared::ECS::Velocity>(entity);
                        RType::Shared::ECS::Clock &clock = _coordinator.getAttribute<RType::Shared::ECS::Clock>(entity);
                        if (now.count() - clock.lastRequest.count() > clock.duration) {
                            RType::Shared::ECS::Entity bullet = _coordinator.createEntity("bullet_" + std::to_string(_bulletId));
                            _coordinator.addAttribute<RType::Server::ECS::Position>(bullet, {pos.x - 150.f, pos.y + 45.f});
                            RType::Shared::Packet packetBullet = RType::Shared::createPacket("Shoot", std::to_string(_bulletId) + "|" + std::to_string(pos.x - 170.f) + "|" + std::to_string(pos.y + 45.f) + "|-20.f|0.f|2");
                            _bulletId++;
                            _toSend.push(packetBullet);
                            clock.lastRequest = now;
                        }
                        pos.y += vel.y;
                        pos.x += vel.x;
                        if (pos.x < -200.f) {
                            RType::Shared::Packet packet = RType::Shared::createPacket("Destroy", entityType.value + "|" + "0");
                            _coordinator.destroyEntity(entity);
                            _toSend.push(packet);
                            createEnemy({2000.f, static_cast<float>(rand() % 600)});
                            continue;
                        }
                        RType::Shared::Packet packet = RType::Shared::createPacket("Move", std::to_string(pos.x) + "|" + std::to_string(pos.y) + "|" + entityType.value);
                        _toSend.push(packet);
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }

        void Game::createWave(void)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> disY(100, 800);
            std::uniform_int_distribution<> disX(2000, 2500);
            float posY = disY(gen);
            float posX = disX(gen);

            for (;_nbEnemies < std::stoi(_enemiesMap[_wave][5]); _nbEnemies++) {
                createEnemy({posX, posY});
                posY = disY(gen);
                posX = disX(gen);
            }
            _isWaveLoaded = true;
        }

        void Game::loadEnemiesMap(void)
        {
            int key;
            std::string line;
            std::ifstream file_stream;
            std::smatch cmd;
            file_stream.open("server/Bestiaire.txt");
            if (!file_stream.is_open())
                std::cout << "Error: file not found" << std::endl;
            while (file_stream.good()) {
                std::getline(file_stream, line);
                if (line[0] == '#')
                    continue;
                line = std::regex_replace(line, std::regex("\\s{2,}"), " ");
                std::regex_search(line, cmd, std::regex("^[0-9]+"));
                key = std::stoi(cmd[0]);
                _enemiesMap[key] = RType::Shared::parsePacket(line);
            }
            file_stream.close();
            for (auto &enemy : _enemiesMap) {
                std::cout << enemy.first << "-"; 
                for (auto &data : enemy.second)
                    std::cout << data << "|";
                std::cout << std::endl;
            }
        }
    } // namespace Server
    
} // namespace RType
