/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** HandleReceived
*/

#include "../Application.hpp"
#include "MenuUDP.hpp"

namespace RType
{
    namespace Client
    {
        void MenuUDP::handleWelcome(RType::Shared::Packet packet)
        {
            if (_app.getCurrentScene() != "Splash")
                _app.changeScene("Menu");
            else
                _app.setBootScene("Menu");
        }

        void MenuUDP::handleDebug(RType::Shared::Packet packet)
        {
            std::cout << "Debug mode activated" << std::endl;
            _debug = true;
        }

        void MenuUDP::handleBye(RType::Shared::Packet packet)
        {
            if (_uuid.compare(packet._body) == 0)
            {
                _socket.close();
                exit(0);
            }
        }

        void MenuUDP::handleRoomList(RType::Shared::Packet packet)
        {
            if (std::string(packet._body).length() <= 3)
            {
                _roomsList.clear();

                if (_app.getCurrentScene() != "RoomList")
                    return;

                for (auto &entity : _app.getCoordinator().getEntities())
                {
                    try
                    {
                        if (_app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity).value == "serverInfo")
                            _app.getCoordinator().destroyEntity(entity);
                    }
                    catch (...)
                    {
                    }
                }
            }
            else
            {
                _roomsList.push_back(packet._body);

                if (_app.getCurrentScene() != "RoomList")
                    return;

                std::vector<std::string> serverInfo = RType::Shared::parsePacket(packet._body);

                RType::Shared::ECS::Entity _tmpEntity;

                _tmpEntity = _app.getCoordinator().createEntity("serverInfo");
                RType::Client::ECS::RectangleShape &rectContainer = _app.getCoordinator().addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({_app.getWindow().getSize().x * 0.7f, (_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 16.f}, {_app.getWindow().getSize().x * 0.3f, SECTION_HEADER_HEIGHT + ((_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 16.f) * (_roomsList.size() - 1)}).getRectangleShape()});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text(serverInfo[2] + " / 4 - " + serverInfo[1] + " - " + serverInfo[0], rectContainer.value.getGlobalBounds(), {0.025f, 0.45f}, 30).getText(), RType::Client::Graphics::Font().getFont()});

                // Button
                _tmpEntity = _app.getCoordinator().createEntity("serverInfo");
                RType::Client::ECS::RectangleShape &rectButton = _app.getCoordinator().addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({_app.getWindow().getSize().x * 0.06f, (_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 32.f}, {_app.getWindow().getSize().x * 0.9f, SECTION_HEADER_HEIGHT + ((_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 16.f) * (_roomsList.size() - 1) + (rectContainer.value.getGlobalBounds().height * .4f - ((_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 64.f))}).getRectangleShape()});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(rectButton.value, {200, 200, 200, 0}).getRectangleShape()}, HOVER_TRANSITION});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Connect", rectButton.value.getGlobalBounds(), {0.025f, 0.45f}, 30).getText(), RType::Client::Graphics::Font().getFont()});
                _app.getCoordinator().addAttribute<RType::Client::ECS::ServerRequest>(_tmpEntity, {"JoinRoom", serverInfo[1], _tmpEntity});
            }
        }

        void MenuUDP::handleCreateRoom(RType::Shared::Packet packet)
        {
            std::string body(packet._body);
            _isInRoom = true;
            _roomUUID = body.substr(body.find("|") + 1);
            _app.changeScene("Room");
        }

        void MenuUDP::handleJoinRoom(RType::Shared::Packet packet)
        {
            std::string body(packet._body);
            _isInRoom = true;
            _roomUUID = body.substr(0, body.find("|"));
            _app.changeScene("Room");
        }

        void MenuUDP::handleRoomFull(RType::Shared::Packet packet)
        {
            std::cout << "Room is full" << std::endl;
        }

        void MenuUDP::handleRoomNotExist(RType::Shared::Packet packet)
        {
            std::cout << "Room does not exist" << std::endl;
        }

        void MenuUDP::handleRoomAlreadyInRoom(RType::Shared::Packet packet)
        {
            std::cout << "Already in room" << std::endl;
        }

        void MenuUDP::handleLeaveRoom(RType::Shared::Packet packet)
        {
            std::cout << "Successfully left room" << std::endl;
            _isInRoom = false;
            _roomUUID.clear();
            _app.changeScene("RoomList");
        }

        void MenuUDP::handleNotInRoom(RType::Shared::Packet packet)
        {
            std::cout << "Not in room" << std::endl;
        }

        void MenuUDP::handlePlayerReady(RType::Shared::Packet packet)
        {
            std::cout << "Player ready to play" << std::endl;
            _isReady = true;
            sendGetRoomInfo();
        }

        void MenuUDP::handlePlayerNotReady(RType::Shared::Packet packet)
        {
            std::cout << "Player not ready" << std::endl;
            _isReady = false;
            sendGetRoomInfo();
        }

        void MenuUDP::handlePlayerMove(RType::Shared::Packet packet)
        {
            std::vector<std::string> data = RType::Shared::parsePacket(packet._body);

            std::cout << "Player move: " << data[0] << " " << data[1] << " " << data[2] << std::endl;

            for (auto &entity : _app.getCoordinator().getEntities())
            {
                try
                {
                    if (_app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity).value == "player")
                        _app.getCoordinator().getAttribute<RType::Client::ECS::Sprite>(entity).value.move(std::stof(data[1]), std::stof(data[2]));
                }
                catch (...)
                {
                }
            }
        }

        void MenuUDP::handlePlayerInGame(RType::Shared::Packet packet)
        {
            std::cout << "Player in game" << std::endl;
            _isInGame = true;
            sendPlayerInGame();
        }

        void MenuUDP::handleRoomInfo(RType::Shared::Packet packet)
        {
            if (std::string(packet._body).length() <= 4)
            {
                _playersList.clear();

                if (_app.getCurrentScene() != "Room")
                    return;

                for (auto &entity : _app.getCoordinator().getEntities())
                {
                    try
                    {
                        if (_app.getCoordinator().getAttribute<RType::Shared::ECS::EntityType>(entity).value == "playerInfo")
                            _app.getCoordinator().destroyEntity(entity);
                    }
                    catch (...)
                    {
                    }
                }
            }
            else
            {
                _playersList.push_back(packet._body);

                if (_app.getCurrentScene() != "Room")
                    return;

                std::vector<std::string> playerInfo = RType::Shared::parsePacket(packet._body);

                RType::Shared::ECS::Entity _tmpEntity;

                _tmpEntity = _app.getCoordinator().createEntity("playerInfo");
                RType::Client::ECS::RectangleShape &rectContainer = _app.getCoordinator().addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({_app.getWindow().getSize().x * 0.7f, (_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 4.f}, {0.f, SECTION_HEADER_HEIGHT + ((_app.getWindow().getSize().y - SECTION_HEADER_HEIGHT) / 4.f) * (_playersList.size() - 1)}).getRectangleShape()});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
                _app.getCoordinator().addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text((playerInfo[2] == "0" ? "Not Ready - " : "Ready - ") + playerInfo[1], rectContainer.value.getGlobalBounds(), {0.025f, 0.45f}, 60).getText(), RType::Client::Graphics::Font().getFont()});
            }
        }

        void MenuUDP::handleGameLaunch(RType::Shared::Packet packet)
        {
            std::cout << "Game launch on port: " << packet._body << std::endl;
            int port = std::stoi(packet._body);

            // std::random_device rd;
            // std::mt19937 gen(rd());
            // std::uniform_int_distribution<> dis(1024, 65535);
            // int localPort = dis(gen);

            // _gsocket = std::make_shared<asio::ip::udp::socket>(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), localPort));
            // _gsocket->send_to(asio::buffer("Hello"), asio::ip::udp::endpoint(_host, port));
            _game = std::make_shared<RType::Client::GameUDP>(_app, _io_context, _host, port, _username, _debug);
            _app.changeScene("Game");
            _game->run();
        }

        void MenuUDP::handleKickPlayer(RType::Shared::Packet packet)
        {
            std::string body(packet._body);

            if (body.compare("ok") == 0)
            {
                sendRoomList();
            }
            else if (body.compare("Kicked") == 0)
            {
                _isInRoom = false;
                _roomUUID.clear();
                _isReady = false;
                _isInGame = false;
                _app.changeScene("RoomList");
            }
        }

        void MenuUDP::handleRoomLock(RType::Shared::Packet packet)
        {
            std::string body(packet._body);

            if (body.compare("0") == 0)
            {
                // Room is now unlocked
            }
            else
            {
                // Room is now locked
            }
        }
    }
}
