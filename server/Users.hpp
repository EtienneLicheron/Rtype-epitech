/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Users
*/

#ifndef USERS_HPP_
#define USERS_HPP_

#include <asio.hpp>
#include <string>
#include <iostream>
#include "UUID.hpp"

namespace RType
{
    namespace Server
    {
        class Users
        {
        public:
            /// @brief constructor of the user
            /// @param endpoint endpoint of the user
            /// @param username username of the user
            Users(asio::ip::udp::endpoint endpoint, std::string username);
            ~Users();

            /// @brief get the uuid of the user
            /// @return return the uuid of the user
            asio::ip::udp::endpoint getEndpoint() const { return _endpoint; }

            /// @brief get the username of the user
            /// @return return the username of the user
            std::string getUsername() const { return _username; }

            /// @brief get the uuid of the user
            /// @return return the uuid of the user
            std::string getUUID() const { return _uuid; }

            /// @brief get the game endpoint of the user
            /// @return return the game endpoint of the user
            asio::ip::udp::endpoint getGameEndpoint() { return _gameEndpoint; }

            /// @brief get the player number of the user
            /// @return return the player number of the user
            std::string getPlayerNumber() { return _player; }

            /// @brief check if the user is in a room
            /// @return return true if the user is in a room, else return false
            bool isInRoom() const { return _in_room; }

            /// @brief check if the user is ready
            /// @return return true if the user is ready, else return false
            bool isReady() const { return _ready; }

            /// @brief set the user in a room
            /// @param in_room true if the user is in a room, false if not
            void setInRoom(const bool in_room) { _in_room = in_room; }

            /// @brief set the user ready if the user is in a room he can't be ready
            /// @param ready true if the user is ready, false if not
            void setReady(const bool ready)
            {
                _ready = ready;
            }

            /// @brief set the username of the user
            /// @param username username of the user
            void setUsername(const std::string username) { _username = username; }

            /// @brief set player number of the user
            /// @param player_number player number of the user
            void setPlayerNumber(std::string player_number) { _player = player_number; }

            /// @brief set the game endpoint of the user
            /// @param endpoint endpoint of the game
            void setGameEndpoint(const asio::ip::udp::endpoint endpoint) { _gameEndpoint = endpoint; }

            /**
             * @brief Print the user information
             */
            void print() const
            {
                std::cout << "\nUsername: " << _username << std::endl;
                std::cout << "UUID: " << _uuid << std::endl;
                std::cout << "Endpoint: " << _endpoint.address().to_string() << ":" << _endpoint.port() << std::endl;
                std::string in_room = _in_room ? "true" : "false";
                std::cout << "In room: " << in_room << std::endl;
                std::string ready = _ready ? "true" : "false";
                std::cout << "Ready: " << ready << std::endl
                          << std::endl;
            };

        private:
            std::string _uuid;
            std::string _username;
            std::string _player;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::endpoint _gameEndpoint;
            bool _in_room;
            bool _ready;
        };
    }
}

#endif /* !USERS_HPP_ */
