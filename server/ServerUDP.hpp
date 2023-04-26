/*
** EPITECH PROJECT, 2022
** B-CPP-500 - RType
** File description:
** ServerUDP
*/

#ifndef __SERVERUDP_HPP__
#define __SERVERUDP_HPP__

#include <asio.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <array>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <map>
#include <random>
#include "Game.hpp"
#include "Users.hpp"
#include "Packet.hpp"
#include "Utils.hpp"
#include "Exception.hpp"
#include "UUID.hpp"
#include "Room.hpp"
#include "LockedQueue.hpp"
#include "Bestiaire.hpp"

#define MAX_BUFF_SIZE 128 + 32 + sizeof(uint16_t) + sizeof(time_t)

namespace RType
{
    namespace Server
    {
        typedef std::pair<RType::Shared::Packet, RType::Server::Users&> ClientPacket;
        class UDPServer;
        typedef void (UDPServer::*function)(ClientPacket);
        class UDPServer
        {
        public:
            /// @brief Constructor of the UDP server
            /// @param port port of the server
            UDPServer(std::string port, bool debug = false);
            ~UDPServer();

            bool hasMessage();
            ClientPacket popMessage();

            /// @brief send packet to a client
            /// @param packet packet to send
            /// @param uuid uuid of the client
            void sendToClient(RType::Shared::Packet packet, std::string uuid);

            /// @brief send packet to all client in room
            /// @param packet packet to send
            /// @param roomUUID uuid of the room
            void sendToAllInRoom(RType::Shared::Packet packet, RType::Server::Room room);

            /// @brief send packet to all client
            /// @param packet packet to send
            void sendToAll(RType::Shared::Packet packet);

            /// @brief get number of client connected
            /// @return number of client connected
            size_t getNbClient();

            /// @brief get client by uuid
            /// @param uuid uuid of the client
            /// @return client
            RType::Server::Users &getClientByUUID(std::string uuid);

            /// @brief get room by uuid of user
            /// @param uuid user uuid to find
            /// @return room where the user uuid is
            RType::Server::Room &getRoomByUserUUID(std::string uuid);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _serverEndP;
            asio::ip::udp::endpoint _remoteEndP;
            std::array<char, MAX_BUFF_SIZE> _recvBuffer;
            std::thread _thread;

            RType::Shared::LockedQueue<ClientPacket> _messages;
            std::vector<RType::Server::Users> _clients;
            std::vector<RType::Server::Room> _rooms;
            std::vector<std::shared_ptr<RType::Server::Game>> _games;
            bool _debug_mode;

            void run();
            void startReceive();
            RType::Shared::Packet getPacketFromBuffer();
            void handleReceive(const asio::error_code &error, std::size_t bytesReceived);
            void send(RType::Shared::Packet packet, asio::ip::udp::endpoint endpoint);

            RType::Server::Users &getOrCreateClient(asio::ip::udp::endpoint endpoint);

            /**
             * @brief Get the Client By Endpoint object
             * @param endpoint
             * @return User who have this endpoint
             */
            RType::Server::Users &getClientByEndpoint(asio::ip::udp::endpoint endpoint);
            void removeClient(std::string uuid);
            void removeRoom(std::string uuid);

            /* Handling system*/
            std::map<std::string, function> _functionsPacket;

            /// @brief handle packet of type Hello
            /// @param packet
            void handleHello(ClientPacket cltPck);

            /// @brief handle packet of type Exit
            /// @param packet
            void handleExit(ClientPacket cltPck);

            /// @brief handle packet of type CreateRoom
            /// @param packet
            void handleCreateRoom(ClientPacket cltPck);

            /// @brief handle packet of type RoomList
            /// @param packet
            void handleRoomList(ClientPacket cltPck);

            /// @brief handle packet of type JoinRoom
            /// @param packet
            void handleJoinRoom(ClientPacket cltPck);

            /// @brief handle packet of type LeaveRoom
            /// @param packet
            void handleLeaveRoom(ClientPacket cltPck);

            /// @brief handle packet of type Ready
            /// @param packet
            void handleReady(ClientPacket cltPck);

            /// @brief handle packet of type InGame
            /// @param packet
            void handleInGame(ClientPacket cltPck);

            /// @brief handle packet of type RoomInfo
            /// @param packet
            void handleRoomInfo(ClientPacket cltPck);

            /// @brief handle packet of type Kick
            /// @param packet
            void handleKick(ClientPacket cltPck);

            /// @brief handle packet of type RoomLock
            /// @param packet
            void handleRoomLock(ClientPacket cltPck);
        };
    }
}

#endif /* !__SERVERUDP_HPP__ */
