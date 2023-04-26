/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** InGame
*/

#include "GameUDP.hpp"
#include "../Application.hpp"

/********** Constructor & Destructor **********/

RType::Client::GameUDP::GameUDP(Application &app, asio::io_context &io_context, asio::ip::address host, int port, std::string username, bool debug) : _app(app), _io_context(io_context),  _serverEndP(host, port), _debug(debug)  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1024, 65535);
    int localPort = dis(gen);

    _username = username;
    _socket = std::make_shared<asio::ip::udp::socket>(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), localPort));
    _running = true;
    _handleFunctions["Spawn"] = &GameUDP::handleSpawn;
    _handleFunctions["SpawnEnemy"] = &GameUDP::handleSpawnEnemy;
    _handleFunctions["Move"] = &GameUDP::handleMove;
    _handleFunctions["Shoot"] = &GameUDP::handleShoot;
    _handleFunctions["Destroy"] = &GameUDP::handleDestroy;
    // run();
}

RType::Client::GameUDP::~GameUDP() {
    _socket->close();
}

/********** Constructor & Destructor End **********/




/********** Public Methods **********/

void RType::Client::GameUDP::send(const RType::Shared::Packet &packet) {
    asio::streambuf b;
    auto buff = b.prepare(sizeof(RType::Shared::Packet));
    std::ostream os(&b);
    os << packet;
    _socket->send_to(buff, _serverEndP);
    if (_debug) {
        std::cout << "Client: " << _username << " sent packet: " << std::endl; 
        std::cout << "Tick: " << packet._tick << std::endl;
        std::cout << "Timestamp: " << packet._timestamp << std::endl;
        std::cout << "Type: " << packet._type << std::endl;
        std::cout << "Body: " << packet._body << std::endl << std::endl;
    }

}

void RType::Client::GameUDP::run() {
    send(RType::Shared::createPacket("HelloGame", _username));
    startReceive();
    while (_running) {
        _io_context.run();
        _io_context.poll();
        _io_context.restart();
    }
}

std::string RType::Client::GameUDP::getPlayer() const {
    return _player;
}
/********** Public Methods End **********/




/********** Private Methods **********/

void RType::Client::GameUDP::startReceive() {
    _socket->async_receive(asio::buffer(_recvBuff),
        [this](std::error_code ec, std::size_t bytes_recvd) {
            handleReceive(ec, bytes_recvd);
        });
}

RType::Shared::Packet RType::Client::GameUDP::getPacketFromBuffer() {
    RType::Shared::Packet packet;
    char *tmp = (char *)malloc(sizeof(char) * MAX_BUFF_SIZE);
    std::string str(_recvBuff.data());
    std::stringstream ss(str);
    int i = 0;

    ss.getline(tmp, sizeof(packet), ';');
    packet._tick = std::atoi(tmp);
    ss.getline(tmp, sizeof(packet), ';');
    packet._timestamp = std::atoi(tmp);
    ss.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._type[i] = tmp[i];
    packet._type[i] = '\0';
    ss.getline(tmp, sizeof(packet), ';');
    for (i = 0; i < strlen(tmp); i++)
        packet._body[i] = tmp[i];
    packet._body[i] = '\0';
    free(tmp);
    _recvQueue.push(packet);

    if (_debug) {
        if (std::string(packet._type) != "Move") {
            std::cout << "Client: " << _username << " received packet: " << std::endl;
            std::cout << "Tick: " << packet._tick << std::endl;
            std::cout << "Timestamp: " << packet._timestamp << std::endl;
            std::cout << "Type: " << packet._type << std::endl;
            std::cout << "Body: " << packet._body << std::endl << std::endl;
        }
    }

    return packet;
}

void RType::Client::GameUDP::handleReceive(const asio::error_code &error, std::size_t bytes_transferred) {
    if (!error) {
        RType::Shared::Packet packet = getPacketFromBuffer();
        if (_handleFunctions.find(packet._type) != _handleFunctions.end())
            (this->*_handleFunctions[packet._type])(packet);
    }
    startReceive();
}

/********** Private Methods End **********/