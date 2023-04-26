/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Menu
*/

#ifndef MENUUDP_HPP_
#define MENUUDP_HPP_

#include "../AttributeClient.hpp"
#include "Utils.hpp"
#include "UUID.hpp"
#include "Exception.hpp"
#include "LockedQueue.hpp"
#include "Bestiaire.hpp"
#include "GameUDP.hpp"

#include "ECS/Attribute.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Coordinator.hpp"

#define MAX_BUFF_SIZE 128 + 32 + sizeof(uint16_t) + sizeof(time_t)

namespace RType
{
    namespace Client
    {
        class Application;
        class MenuUDP;
        typedef void (MenuUDP::*function)(RType::Shared::Packet);
        class MenuUDP
        {
            public:
                /**
                 * @brief Construct a new Menu U D P object
                 *
                 * @param app the application
                 * @param host the host
                 * @param port the port
                 * @param username the username
                 * @param localPort the local port
                 */
                MenuUDP(Application &app, asio::ip::address host, unsigned short port, std::string username, unsigned short localPort = 0);

                /**
                 * @brief Destroy the Menu U D P object
                 */
                MenuUDP(const MenuUDP &cpy);

                ~MenuUDP();

                /**
                 * @brief Send a packet to the game server
                 *
                 * @param address the address
                 * @param port the port
                 * @param username the username
                 */
                void reset(std::string address, unsigned short port, std::string username);

                /**
                 * @brief Send a packet to the game server
                 * @param packet Packet to send
                 */
                void send(const RType::Shared::Packet &packet);

                /**
                 * @brief Send a packet to the game server
                 * @param packet Packet to send
                 */
                bool hasMessage();

                /**
                 * @brief Send a packet to the game server
                 * @param packet Packet to send
                 */
                RType::Shared::Packet popMessage();

                /* Function packet */

                /// @brief send login packet
                /// @param username username of the client
                void sendLogin(std::string username);

                /// @brief send logout packet
                void sendDisconnect();

                /// @brief create a room
                void sendNewRoom(std::string roomName);

                /// @brief list all room set the result in _roomsList (vector of Room), you can get it with getRoomsList()
                void sendRoomList();

                /// @brief join a room
                /// @param roomUUID UUID of the room
                void sendJoinRoom(std::string roomUUID);

                /// @brief leave a room
                void sendLeaveRoom();

                /// @brief set player ready
                void sendPlayerReady();

                /// @brief send player is in game
                void sendPlayerInGame();

                /// @brief get player list in room
                void sendGetRoomInfo();

                /// @brief send kick player
                /// @param toKickUUID uuid of the player to kick
                void sendKickPlayer(std::string toKickUUID);

                /// @brief send room lock
                void sendRoomLock();

                /// @brief send player movement
                // void sendMove(std::string direction);


                // get _game
                std::shared_ptr<RType::Client::GameUDP> getGame();
                /* Getters */

                std::string getUsername();

                /// @brief get the list of room, is set by sendRoomList()
                /// @return vector of Room
                std::vector<std::string> &getRoomsList();
                std::vector<std::string> &getPlayersList();

            private:
                Application &_app;

                asio::io_context _io_context;
                asio::ip::udp::socket _socket;
                // std::shared_ptr<asio::ip::udp::socket> _gsocket;
                std::shared_ptr<RType::Client::GameUDP> _game;
                asio::ip::udp::endpoint _serverEndP;
                asio::ip::udp::endpoint _remoteEndP;
                std::array<char, MAX_BUFF_SIZE> _recvBuffer;
                std::thread _thread;

                RType::Shared::LockedQueue<RType::Shared::Packet> _messages;

                asio::ip::address _host;
                std::string _uuid;
                std::string _username;
                std::string _roomUUID;
                bool _isInRoom;
                bool _isReady;
                bool _isInGame;
                bool _debug;

                /// @brief list all room set by sendRoomList()
                std::vector<std::string> _roomsList;
                /// @brief list all player in room set by sendGetRoomInfo()
                std::vector<std::string> _playersList;

                void handleReceive(const asio::error_code &error, std::size_t bytes_transferred);
                void startReceive();
                RType::Shared::Packet getPacketFromBuffer();
                void run();

                /* Handling system*/
                std::map<std::string, function> _functionsPacket;

                /// @brief handle welcome packet
                /// @param packet packet received
                void handleWelcome(RType::Shared::Packet packet);

                /// @brief handle debug packet
                /// @param packet packet received
                void handleDebug(RType::Shared::Packet packet);

                /// @brief handle bye packet
                /// @param packet packet received
                void handleBye(RType::Shared::Packet packet);

                /// @brief handle list room packet
                /// @param packet packet received
                void handleRoomList(RType::Shared::Packet packet);

                /// @brief handle room created packet
                /// @param packet packet received
                void handleCreateRoom(RType::Shared::Packet packet);

                /// @brief handle room joined packet
                /// @param packet packet received
                void handleJoinRoom(RType::Shared::Packet packet);

                /// @brief handle room full packet
                /// @param packet packet received
                void handleRoomFull(RType::Shared::Packet packet);

                /// @brief handle room left packet
                /// @param packet packet received
                void handleRoomNotExist(RType::Shared::Packet packet);

                /// @brief handle room left packet
                void handleRoomAlreadyInRoom(RType::Shared::Packet packet);

                /// @brief handle room left packet
                /// @param packet packet received
                void handleLeaveRoom(RType::Shared::Packet packet);

                /// @brief handle room left packet
                /// @param packet packet received
                void handleNotInRoom(RType::Shared::Packet packet);

                /// @brief handle ready packet
                /// @param packet packet received
                void handlePlayerReady(RType::Shared::Packet packet);

                /// @brief handle ready packet
                /// @param packet packet received
                void handlePlayerNotReady(RType::Shared::Packet packet);

                /// @brief handle player move packet
                /// @param packet packet received
                void handlePlayerMove(RType::Shared::Packet packet);

                /// @brief handle player in game packet
                /// @param packet packet received
                void handlePlayerInGame(RType::Shared::Packet packet);

                /// @brief handle room info packet
                /// @param packet packet received
                void handleRoomInfo(RType::Shared::Packet packet);

                /// @brief handle game launch packet (start game)
                /// @param packet packet received
                void handleGameLaunch(RType::Shared::Packet packet);

                /// @brief handle kick player packet
                /// @param packet packet received
                void handleKickPlayer(RType::Shared::Packet packet);

                /// @brief handle wave packet
                /// @param packet packet received
                void handleWave(RType::Shared::Packet packet);

                /// @brief handle player locked room packet
                /// @param packet packet received
                void handleRoomLock(RType::Shared::Packet packet);
        };
    }
}

#endif /* !MENUUDP_HPP_ */
