/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Game
*/

#ifndef __GAME_HPP_
#define __GAME_HPP_

#define TICKS 20

#include <asio.hpp>
#include <map>
#include <thread>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <functional>
#include <fstream>
#include <regex>

#include "AttributeServer.hpp"
#include "Users.hpp"
#include "Room.hpp"
#include "Packet.hpp"
#include "Utils.hpp"
#include "Exception.hpp"
#include "LockedQueue.hpp"
// #include "Bestiaire.hpp"
#include "UpdatePlayers.hpp"
#include "UpdateEnemy.hpp"

#include "ECS/Attribute.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Coordinator.hpp"

#define MAX_BUFF_SIZE 128 + 32 + sizeof(uint16_t) + sizeof(time_t)

namespace RType
{
    namespace Server
    {
        typedef std::pair<RType::Shared::Packet, RType::Server::Users &> PlayerPacket;
        class Game;
        typedef void (Game::*functionPtr)(PlayerPacket);
        /**
         * @brief Class that will manage game logic & multi-threading
         */
        class Game
        {
        public:
            Game(std::string port, RType::Server::Room &room, bool debug = false);
            ~Game();

            bool hasMessage();
            PlayerPacket popMessage();

            /**
             * @brief Send a packet to all client in room
             * @param packet The packet to send
             */
            void sendToAllInRoom(RType::Shared::Packet packet);

            RType::Server::Room &getRoomInGame();

        private:
            void registerAttributes();

            /**
             * @brief The infinite loop of the game
             */
            void infiniteLoop();

            /**
             * @brief The infinite loop of the game
             */
            void getData();

            /**
             * @brief Start receiving packets from clients
             */
            void startReceiving();

            void getPacketFromBuffer();

            /**
             * @brief Handle the received packet
             * @param error The error code
             * @param bytesTransferred The number of bytes received
             */
            void handleReceive(const asio::error_code &error, std::size_t bytesReceived);

            RType::Server::Users &getClient(asio::ip::udp::endpoint endpoint, std::string name);

            /**
             * @brief  Handle the start of the game
             */
            void handleStart(PlayerPacket cliPacket);

            /**
             * @brief  Handle the movements of players
             */
            void handleMove(PlayerPacket cliPacket);

            /**
             * @brief  Handle the shooting of players
             */
            void handleShoot(PlayerPacket cliPacket);

            /**
             * @brief  Handle the player shooting the enemy
             */
            void handleHit(PlayerPacket cliePacket);

            /**
             * @brief  Handle the destroy of an entity
             */
            void handleDestroy(PlayerPacket cliPacket);

            /**
             * @brief  Handle the collision between player and enemy
             */
            void handleCollision(PlayerPacket cliPacket);

            /**
             * @brief  Handle the isLoaded of Game
             */

            void handleGameLoaded(PlayerPacket cliPacket);

            /**
             * @brief We keep the thread to join it in the destructor
             */
            std::thread _thread;

            /**
             * @brief The room in game
             */
            RType::Server::Room &_roomInGame;

            asio::io_context _ioContext;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _remotEndP;
            std::array<char, MAX_BUFF_SIZE> _recvBuff;
            RType::Shared::LockedQueue<PlayerPacket> _messages;
            RType::Shared::LockedQueue<RType::Shared::Packet> _toSend;
            std::map<std::string, functionPtr> _packetHandler;
            int _playerId;
            /**
             * @brief The coordinator of the game, so each games / room can have their own entities
             */
            RType::Shared::ECS::Coordinator _coordinator;
            bool _debugMode;

            int _bulletId;

            bool _isGameLoaded;

            /*                                  Enemies Section                                   */
            void createEnemy(RType::Server::ECS::Position pos);
            void updateEnemies(void);
            void createWave(void);
            void loadEnemiesMap(void);
            int _wave;
            int _enemyId;
            int _nbEnemies;
            int _destroyedEnemies;
            bool _isWaveLoaded;
            std::map<int, std::vector<std::string>> _enemiesMap;

            /*                                  Player Section                                   */
            int _hp;
            int _score;
            std::string _player;
        };
    }
}

#endif /* !__GAME_HPP_ */
