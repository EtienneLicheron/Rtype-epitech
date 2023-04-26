/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** MenuUDP
*/

#include "MenuUDP.hpp"

/********** Constructor & Destructor **********/
RType::Client::MenuUDP::MenuUDP(Application &app, asio::ip::address host, unsigned short port, std::string username, unsigned short localPort) : _app(app), _host(host), _serverEndP(host, port), _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), localPort)), _thread(&RType::Client::MenuUDP::run, this)
{
    _username = username;
    _isInRoom = false;
    _isInGame = false;
    _debug = false;
    _uuid = "";
    _functionsPacket["Welcome"] = &RType::Client::MenuUDP::handleWelcome;
    _functionsPacket["Debug"] = &RType::Client::MenuUDP::handleDebug;
    _functionsPacket["Bye"] = &RType::Client::MenuUDP::handleBye;
    _functionsPacket["ListRoom"] = &RType::Client::MenuUDP::handleRoomList;
    _functionsPacket["CreateRoom"] = &RType::Client::MenuUDP::handleCreateRoom;
    _functionsPacket["JoinRoom"] = &RType::Client::MenuUDP::handleJoinRoom;
    _functionsPacket["RoomFull"] = &RType::Client::MenuUDP::handleRoomFull;
    _functionsPacket["RoomNotExist"] = &RType::Client::MenuUDP::handleRoomNotExist;
    _functionsPacket["RoomAlreadyInRoom"] = &RType::Client::MenuUDP::handleRoomAlreadyInRoom;
    _functionsPacket["LeaveRoom"] = &RType::Client::MenuUDP::handleLeaveRoom;
    _functionsPacket["NotInRoom"] = &RType::Client::MenuUDP::handleNotInRoom;
    _functionsPacket["PlayerReady"] = &RType::Client::MenuUDP::handlePlayerReady;
    _functionsPacket["NotReady"] = &RType::Client::MenuUDP::handlePlayerNotReady;
    _functionsPacket["GameStart"] = &RType::Client::MenuUDP::handlePlayerInGame;
    _functionsPacket["Info"] = &RType::Client::MenuUDP::handleRoomInfo;
    _functionsPacket["GamePort"] = &RType::Client::MenuUDP::handleGameLaunch;
    _functionsPacket["Kicked"] = &RType::Client::MenuUDP::handleKickPlayer;
    _functionsPacket["RoomLock"] = &RType::Client::MenuUDP::handleRoomLock;
    // sendLogin(username);
}
RType::Client::MenuUDP::~MenuUDP()
{
    _io_context.stop();
    _thread.join();
}

void RType::Client::MenuUDP::reset(std::string address, unsigned short port, std::string username)
{
    address = address == "localhost" ? "127.0.0.1" : address;
    _host = asio::ip::make_address(address);
    _username = username;
    _serverEndP = asio::ip::udp::endpoint(_host, port);
    _socket = asio::ip::udp::socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
    _isInRoom = false;
    _isInGame = false;
    _uuid = "";
    sendLogin(username);
}

/********** Constructor & Destructor End **********/

/********** Public Methods **********/

void RType::Client::MenuUDP::send(const RType::Shared::Packet &packet)
{
    asio::streambuf b;
    auto buff = b.prepare(sizeof(packet));
    std::ostream os(&b);
    os << packet;
    _socket.send_to(buff, _serverEndP);
    if (_debug) {
        std::cout << "Client: " << _username << " sent packet: " << std::endl;
        std::cout << "Tick: " << packet._tick << std::endl;
        std::cout << "Timestamp: " << packet._timestamp << std::endl;
        std::cout << "Type: " << packet._type << std::endl;
        std::cout << "Body: " << packet._body << std::endl << std::endl;
    }
}

bool RType::Client::MenuUDP::hasMessage()
{
    return !_messages.empty();
}

RType::Shared::Packet RType::Client::MenuUDP::popMessage()
{
    if (_messages.empty())
        throw std::logic_error("No message to pop");
    return _messages.pop();
}

/********** Getters Methods **********/

std::vector<std::string> &RType::Client::MenuUDP::getRoomsList()
{
    return _roomsList;
}

std::vector<std::string> &RType::Client::MenuUDP::getPlayersList()
{
    return _playersList;
}

/********** Getters Methods End **********/

/********** Private Methods **********/

void RType::Client::MenuUDP::startReceive()
{
    _socket.async_receive_from(asio::buffer(_recvBuffer), _remoteEndP, [this](const asio::error_code &error, std::size_t bytes_transferred)
                               { handleReceive(error, bytes_transferred); });
}

RType::Shared::Packet RType::Client::MenuUDP::getPacketFromBuffer()
{
    RType::Shared::Packet packet;
    char *tmp = (char *)malloc(sizeof(char) * MAX_BUFF_SIZE);
    std::string str(_recvBuffer.data());
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
    _messages.push(packet);

    if (_debug) {
        std::cout << "Client: " << _username << " received packet: " << std::endl;
        std::cout << "Tick: " << packet._tick << std::endl;
        std::cout << "Timestamp: " << packet._timestamp << std::endl;
        std::cout << "Type: " << packet._type << std::endl;
        std::cout << "Body: " << packet._body << std::endl << std::endl;
    }
    return packet;
}

void RType::Client::MenuUDP::handleReceive(const asio::error_code &error, std::size_t bytes_transferred)
{
    if (!error)
    {
        RType::Shared::Packet packet = getPacketFromBuffer();
        if (_functionsPacket.find(packet._type) != _functionsPacket.end())
            (this->*_functionsPacket[packet._type])(packet);
    }
    else
    {
        std::cerr << "Error: " << error.message() << std::endl;
    }
    startReceive();
}

void RType::Client::MenuUDP::run()
{
    startReceive();
    while (_io_context.stopped() == false)
    {
        try
        {
            _io_context.run();
        }
        catch (RType::Shared::Exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

std::string RType::Client::MenuUDP::getUsername()
{
    return _username;
}

std::shared_ptr<RType::Client::GameUDP> RType::Client::MenuUDP::getGame()
{
    return _game;
}
