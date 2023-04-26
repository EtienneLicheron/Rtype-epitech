/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** InGame
*/

#ifndef INGAME_HPP_
#define INGAME_HPP_

#include <asio.hpp>

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
        class GameUDP;
        typedef void (GameUDP::*handleFunction)(RType::Shared::Packet);
        // ::A &getCoordinator();
        class GameUDP
        {
            public:
                /**
                 * @brief Construct a new Game U D P object
                 *
                 * @param app the application
                 * @param io_context the io context
                 * @param host the host
                 * @param port the port
                 * @param username the username
                 * @param debug the debug
                 */
                GameUDP(Application &app, asio::io_context &io_context, asio::ip::address host, int port, std::string username, bool debug = false);
                ~GameUDP();

                /**
                 * @brief Send a packet to the game server
                 * @param packet Packet to send
                 */
                void send(const RType::Shared::Packet &packet);
                void run();
                std::string getPlayer() const;


                /**
                 * @brief The last collision request
                 */
                std::vector<std::string> _tmpCollision;

                bool checkCollisionRequest(std::string &checkReq) {
                    for (std::string &req : _tmpCollision) {
                        if (req == checkReq)
                            return true;
                    }
                    return false;
                }
            private:
                /* reference to application */
                Application &_app;

                asio::io_context &_io_context;
                /**
                 * @brief Socket used to communicate with the server for the game
                 */
                std::shared_ptr<asio::ip::udp::socket> _socket;

                /**
                 * @brief Endpoint of the game server
                 */
                asio::ip::udp::endpoint _serverEndP;

                /**
                 * @brief Buffer used to receive data from the server
                 */
                std::array<char, MAX_BUFF_SIZE> _recvBuff;

                /**
                 * @brief Locked queue used to store received packets
                 */
                RType::Shared::LockedQueue<RType::Shared::Packet> _recvQueue;

                /**
                 * @brief True if the game is running
                 */
                bool _running;

                /**
                 * @brief Username of the player
                 */
                std::string _username;
                std::string _player;
                bool _debug;

                /**
                 * @brief start receiving data from the game server
                */
                void startReceive();

                /**
                 * @brief Handle received data from the game server
                 * @param error Error code
                 * @param bytes_transferred Number of bytes received
                 */
                RType::Shared::Packet getPacketFromBuffer();

                /*                    Handle functions                          */

                std::map<std::string, handleFunction> _handleFunctions;
                /**
                 * @brief Handle the reception of data from the game server
                 * @param error
                 * @param bytes_transferred
                 */
                void handleReceive(const asio::error_code &error, std::size_t bytes_transferred);

                /**
                 * @brief Handle the reception of spawn request
                 * @param packet Packet received
                 */
                void handleSpawn(RType::Shared::Packet packet);

                /**
                 * @brief Handle the reception of enemy spawn request
                 * @param packet Packet received
                 */
                void handleSpawnEnemy(RType::Shared::Packet packet);

                /**
                 * @brief Handle the reception of move request
                 * @param packet Packet received
                 */
                void handleMove(RType::Shared::Packet packet);

                /**
                 * @brief Handle the reception of shoot request
                 * @param packet Packet received
                 */
                void handleShoot(RType::Shared::Packet packet);

                /**
                 * @brief Handle the reception of destroy request
                 * @param packet Packet received
                 */
                void handleDestroy(RType::Shared::Packet packet);
        };
    }
}

#endif /* !INGAME_HPP_ */
