/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

RType::Server::Game::Game(std::string port, RType::Server::Room &room, bool debug) : _roomInGame(room), _socket(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), std::stoi(port))), _debugMode(debug), _thread(&RType::Server::Game::infiniteLoop, this)
{
    _packetHandler["HelloGame"] = &RType::Server::Game::handleStart;
    _packetHandler["Gameloaded"] = &RType::Server::Game::handleGameLoaded;
    _packetHandler["Move"] = &RType::Server::Game::handleMove;
    _packetHandler["Shoot"] = &RType::Server::Game::handleShoot;
    _packetHandler["Hit"] = &RType::Server::Game::handleHit;
    _packetHandler["Destroy"] = &RType::Server::Game::handleDestroy;
    _packetHandler["Collision"] = &RType::Server::Game::handleCollision;
    _playerId = 1;
    _enemyId = 1;
    _bulletId = 0;
    _nbEnemies = 1;
    _hp = 3;
    _isWaveLoaded = false;
    _isGameLoaded = false;
}

RType::Server::Game::~Game()
{
    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);

    if (_thread.joinable())
        _thread.join();

    _socket.close();
}

void RType::Server::Game::registerAttributes()
{
    _coordinator.registerAttribute<RType::Server::ECS::Position>();
    _coordinator.registerAttribute<RType::Shared::ECS::Speed>();
    _coordinator.registerAttribute<RType::Shared::ECS::Velocity>();
    _coordinator.registerAttribute<RType::Shared::ECS::Health>();
    _coordinator.registerAttribute<RType::Shared::ECS::Clock>();
}

bool RType::Server::Game::hasMessage()
{
    return !_messages.empty();
}

RType::Server::PlayerPacket RType::Server::Game::popMessage()
{
    return _messages.pop();
}

void RType::Server::Game::sendToAllInRoom(RType::Shared::Packet packet)
{
    asio::streambuf b;
    auto buff = b.prepare(sizeof(packet));
    std::ostream os(&b);
    os << packet;

    for (auto &client : _roomInGame.getUser())
    {
        try
        {
            _socket.send_to(buff, client.get().getGameEndpoint());
            if (_debugMode)
            {
                if (std::string(packet._type) == "Move")
                    continue;
                std::cout << "Sent packet to " << client.get().getGameEndpoint().address().to_string() << ":" << client.get().getGameEndpoint().port() << std::endl;
                std::cout << "Tick: " << packet._tick << std::endl;
                std::cout << "Timestamp: " << packet._timestamp << std::endl;
                std::cout << "Type: " << packet._type << std::endl;
                std::cout << "Body: " << packet._body << std::endl
                          << std::endl;
            }
        }
        catch (...)
        {
            std::cout << "Error while sending packet to client" << std::endl;
        }
    }
}

RType::Server::Room &RType::Server::Game::getRoomInGame()
{
    return _roomInGame;
}

void RType::Server::Game::getData()
{
    try
    {
        if (hasMessage())
        {
            PlayerPacket cltPckt = popMessage();
            if (_packetHandler.find(cltPckt.first._type) != _packetHandler.end())
            {
                (this->*_packetHandler[cltPckt.first._type])(cltPckt);
            }
        }
    }
    catch (RType::Shared::Exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void RType::Server::Game::infiniteLoop()
{
    long long unsigned int tick = 0;
    std::chrono::milliseconds last = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    _nbEnemies = 0;
    _wave = 1;
    // Init coordinator
    _coordinator.init();

    // Register Attributes
    registerAttributes();

    // Register Service
    _ioContext.run();

    std::cout << "Game loop started" << std::endl;

    startReceiving();

    std::cout << "end receved" << std::endl;
    loadEnemiesMap();
    while (true)
    {
        now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        getData();
        if (now.count() - last.count() > TICKS)
        {
            last = now;
            tick++;
            if (_isGameLoaded)
            {
                if (!_isWaveLoaded)
                    createWave();
                if (_nbEnemies == 0)
                {
                    _wave++;
                    _isWaveLoaded = false;
                }
                if (_hp <= 0)
                {
                    for (auto &entity : _coordinator.getEntities())
                    {
                        try
                        {
                            RType::Shared::ECS::EntityType type = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
                            if (type.value == _player)
                            {
                                RType::Shared::Packet packet = RType::Shared::createPacket("Destroy", type.value + "|" + "1");
                                _toSend.push(packet);
                                _coordinator.destroyEntity(entity);
                                continue;
                            }
                        }
                        catch (RType::Shared::Exception &e)
                        {
                            std::cout << e.what() << std::endl;
                        }
                    }
                }
                if (_wave > 3)
                    _wave = 1;
                updateEnemies();
            }
            while (_toSend.empty() == false)
            {
                auto packet = _toSend.pop();
                sendToAllInRoom(packet);
            }
        }
        _ioContext.poll();
        _ioContext.restart();
        // TODO: Send/listen data to clients
    }
}

void RType::Server::Game::startReceiving()
{
    _socket.async_receive_from(asio::buffer(_recvBuff), _remotEndP,
                               [this](std::error_code ec, std::size_t bytes)
                               {
                                   handleReceive(ec, bytes);
                               });
}

void RType::Server::Game::getPacketFromBuffer()
{
    RType::Shared::Packet packet;
    char *tmp = (char *)malloc(sizeof(char) * MAX_BUFF_SIZE);
    std::string str(_recvBuff.data());
    std::stringstream ss(str);
    int i = 0;

    ss.getline(tmp, sizeof(packet), ';');
    packet._tick = atoi(tmp);
    ss.getline(tmp, sizeof(packet), ';');
    packet._timestamp = atoi(tmp);
    ss.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._type[i] = tmp[i];
    packet._type[i] = '\0';
    ss.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._body[i] = tmp[i];
    packet._body[i] = '\0';
    free(tmp);

    std::cout << "server ingame - asyncReceivePacket()" << std::endl;
    std::cout << "\ttick:" << packet._tick << std::endl;
    std::cout << "\ttime:" << packet._timestamp << std::endl;
    std::cout << "\ttype:" << packet._type << std::endl;
    std::cout << "\tbody:" << packet._body << "\n"
              << std::endl;
    if (strcmp(packet._type, "HelloGame") == 0)
    {
        std::cout << "SEND HelloGame" << std::endl;
        auto msg = PlayerPacket(packet, getClient(_remotEndP, packet._body));
        _messages.push(msg);
    }
    else
    {
        auto msg = PlayerPacket(packet, getClient(_remotEndP, ""));
        _messages.push(msg);
    }
}

void RType::Server::Game::handleReceive(const asio::error_code &error, std::size_t bytesReceived)
{
    if (!error)
    {
        getPacketFromBuffer();
    }
    else
    {
        std::cout << "Error: " << error.message() << std::endl;
    }
    startReceiving();
}

RType::Server::Users &RType::Server::Game::getClient(asio::ip::udp::endpoint endpoint, std::string name)
{
    for (auto &client : _roomInGame.getUser())
    {
        if (name.compare("") != 0 && client.get().getUsername().compare(name) == 0)
        {
            if (client.get().getGameEndpoint() != endpoint)
                client.get().setGameEndpoint(endpoint);
            return client;
        }
        else if (name.compare("") == 0 && client.get().getGameEndpoint() == endpoint)
            return client;
    }
    throw std::runtime_error("Client not found");
}
