/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** ServerUDP
*/

#include "ServerUDP.hpp"

/****************** Constructor/Destructor ******************/

RType::Server::UDPServer::UDPServer(std::string port, bool debug) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), std::stoi(port))), _debug_mode(debug), _thread(&RType::Server::UDPServer::run, this)
{
    std::cout << "Listening on port " << port << std::endl;
    _functionsPacket["Hello"] = &RType::Server::UDPServer::handleHello;
    _functionsPacket["Exit"] = &RType::Server::UDPServer::handleExit;
    _functionsPacket["CreateRoom"] = &RType::Server::UDPServer::handleCreateRoom;
    _functionsPacket["RoomList"] = &RType::Server::UDPServer::handleRoomList;
    _functionsPacket["JoinRoom"] = &RType::Server::UDPServer::handleJoinRoom;
    _functionsPacket["LeaveRoom"] = &RType::Server::UDPServer::handleLeaveRoom;
    _functionsPacket["Ready"] = &RType::Server::UDPServer::handleReady;
    _functionsPacket["InGame"] = &RType::Server::UDPServer::handleInGame;
    _functionsPacket["RoomInfo"] = &RType::Server::UDPServer::handleRoomInfo;
    _functionsPacket["Kick"] = &RType::Server::UDPServer::handleKick;
    _functionsPacket["RoomLock"] = &RType::Server::UDPServer::handleRoomLock;
}

RType::Server::UDPServer::~UDPServer()
{
    _io_context.stop();
    _thread.join();
}
/****************** Constructor/Destructor End ******************/

/****************** Public Methods ******************/

bool RType::Server::UDPServer::hasMessage()
{
    return !_messages.empty();
}

RType::Server::ClientPacket RType::Server::UDPServer::popMessage()
{
    return _messages.pop();
}

void RType::Server::UDPServer::sendToClient(RType::Shared::Packet packet, std::string uuid)
{
    for (auto &client : _clients)
    {
        if (client.getUUID().compare(uuid) == 0)
        {
            send(packet, client.getEndpoint());
            return;
        }
    }
}

void RType::Server::UDPServer::sendToAllInRoom(RType::Shared::Packet packet, RType::Server::Room room)
{
    std::vector<std::reference_wrapper<RType::Server::Users>> clients = room.getUser();
    for (auto &client : clients)
    {
        send(packet, client.get().getEndpoint());
    }
}

void RType::Server::UDPServer::sendToAll(RType::Shared::Packet packet)
{
    for (auto &client : _clients)
    {
        send(packet, client.getEndpoint());
    }
}

size_t RType::Server::UDPServer::getNbClient()
{
    return _clients.size();
}

RType::Server::Users &RType::Server::UDPServer::getClientByUUID(std::string uuid)
{
    for (auto &client : _clients)
    {
        if (client.getUUID().compare(uuid) == 0)
        {
            return client;
        }
    }
    throw RType::Shared::Exception("Client not found");
}

RType::Server::Room &RType::Server::UDPServer::getRoomByUserUUID(std::string uuid)
{
    for (auto &room : _rooms)
    {
        if (room.userIsInRoom(uuid))
        {
            return room;
        }
    }
    throw RType::Shared::Exception("Room not found");
}

/****************** Public Methods End ******************/

/****************** Private Methods ******************/

void RType::Server::UDPServer::run()
{
    _io_context.run();
    startReceive();
    while (true)
    {
        try
        {
            if (hasMessage()) {
                ClientPacket cltPckt = popMessage();
                auto packet = std::get<0>(cltPckt);
                if (_functionsPacket.find(packet._type) != _functionsPacket.end())
                    (this->*_functionsPacket[packet._type])(cltPckt);
            }
            _io_context.poll();
            _io_context.restart();
        }
        catch (RType::Shared::Exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "Server stopped" << std::endl;
}

void RType::Server::UDPServer::startReceive()
{
    _socket.async_receive_from(asio::buffer(_recvBuffer), _remoteEndP,
                               [this](std::error_code ec, std::size_t bytesReceived)
                               {
                                //    std::cout << "Received " << bytesReceived << " bytes" << std::endl;
                                   handleReceive(ec, bytesReceived);
                               });
}

RType::Shared::Packet RType::Server::UDPServer::getPacketFromBuffer()
{
    RType::Shared::Packet packet;
    char *tmp = (char *)malloc(sizeof(char) * MAX_BUFF_SIZE);
    std::string str(_recvBuffer.data());
    std::stringstream is(str);
    int i = 0;

    is.getline(tmp, sizeof(packet), ';');
    packet._tick = atoi(tmp);
    is.getline(tmp, sizeof(packet), ';');
    packet._timestamp = atoi(tmp);
    is.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._type[i] = tmp[i];
    packet._type[i] = '\0';
    is.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._body[i] = tmp[i];
    packet._body[i] = '\0';
    free(tmp);
    auto msg = ClientPacket(packet, getOrCreateClient(_remoteEndP));
    _messages.push(msg);
    /* Debug */
    if (_debug_mode) {
        std::cout << "Received packet from " << _remoteEndP.address().to_string() << ":" << _remoteEndP.port() << std::endl;
        std::cout << "Tick: " << packet._tick << std::endl;
        std::cout << "Timestamp: " << packet._timestamp << std::endl;
        std::cout << "Type: " << packet._type << std::endl;
        std::cout << "Body: " << packet._body << std::endl << std::endl;
    }
    return (packet);
}

void RType::Server::UDPServer::handleReceive(const asio::error_code &error, std::size_t bytesReceived)
{
    if (!error)
    {
        try
        {
            RType::Shared::Packet packet = getPacketFromBuffer();
            // if (_functionsPacket.find(packet._type) != _functionsPacket.end())
            // {
            //     (this->*_functionsPacket[packet._type])(packet);
            // }
        }
        catch (RType::Shared::Exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: " << error.message() << std::endl;
    }
    startReceive();
}

void RType::Server::UDPServer::send(RType::Shared::Packet packet, asio::ip::udp::endpoint endpoint)
{
    asio::streambuf b;
    auto buff = b.prepare(sizeof(packet));
    std::ostream os(&b);

    os << packet;
    _socket.send_to(buff, endpoint);

    if (_debug_mode) {
        std::cout << "Sent packet to " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
        std::cout << "Tick: " << packet._tick << std::endl;
        std::cout << "Timestamp: " << packet._timestamp << std::endl;
        std::cout << "Type: " << packet._type << std::endl;
        std::cout << "Body: " << packet._body << std::endl << std::endl;
    }
}

RType::Server::Users &RType::Server::UDPServer::getOrCreateClient(asio::ip::udp::endpoint endpoint)
{
    for (auto &client : _clients)
        if (client.getEndpoint() == endpoint)
            return client;
    RType::Server::Users client(endpoint, "Username");
    _clients.push_back(std::move(client));
    if (_debug_mode)
        send(RType::Shared::createPacket("Debug", ""), endpoint);
    return _clients.back();
}

RType::Server::Users &RType::Server::UDPServer::getClientByEndpoint(asio::ip::udp::endpoint endpoint)
{
    for (auto &client : _clients)
        if (client.getEndpoint() == endpoint)
            return client;
    throw RType::Shared::Exception("Client not found");
}


void RType::Server::UDPServer::removeClient(std::string uuid)
{
    for (auto it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->getUUID().compare(uuid) == 0)
        {
            _clients.erase(it);
            return;
        }
    }
}

void RType::Server::UDPServer::removeRoom(std::string uuid)
{
    for (auto it = _rooms.begin(); it != _rooms.end(); it++)
    {
        if (it->getUUID().compare(uuid) == 0)
        {
            _rooms.erase(it);
            return;
        }
    }
}

/****************** Private Methods End ******************/