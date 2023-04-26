/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <vector>
#include "Users.hpp"
#include "UUID.hpp"

#define MAX_CLIENT 4

namespace RType {
    namespace Server {
        class Room {
            public:
                Room(std::string name, RType::Server::Users& user_sender_req);
                ~Room();

                std::string getName() const;
                std::string getUUID() const;
                std::string getOwnerUUID() const;
                size_t getNbUsers() const;
                bool isLocked() const;
                bool isGameStarted() const;

                std::vector<std::reference_wrapper<RType::Server::Users>> &getUser();

                bool addUser(RType::Server::Users& user);
                bool removeUser(std::string user_uuid);
                bool userIsInRoom(std::string user_uuid);
                void setLocked(bool locked);
                void setGameStarted(bool started);
            protected:
            private:
                std::vector<std::reference_wrapper<RType::Server::Users>> _users;
                std::string _uuid;
                std::string _name;
                std::string _owner_uuid;
                bool _is_locked;
                bool _is_ingame;

        };
    }
}


#endif /* !ROOM_HPP_ */
