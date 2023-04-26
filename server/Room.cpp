/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Room
*/

#include "Room.hpp"

/********** Constructor & Destructor **********/

RType::Server::Room::Room(std::string name, RType::Server::Users& user_sender_req) : _name(name) {
    _uuid = RType::Shared::UUID::generate();
    _owner_uuid = user_sender_req.getUUID();
    _users.push_back(user_sender_req);
    _is_locked = false;
    _is_ingame = false;
}


RType::Server::Room::~Room() {
}

/********** Constructor & Destructor End **********/



/********** Getter **********/

std::string RType::Server::Room::getName() const {
    return _name;
}

std::string RType::Server::Room::getOwnerUUID() const {
    return _owner_uuid;
}

std::string RType::Server::Room::getUUID() const {
    return _uuid;
}

size_t RType::Server::Room::getNbUsers() const {
    return _users.size();
}

std::vector<std::reference_wrapper<RType::Server::Users>> &RType::Server::Room::getUser() {
    return _users;
}

bool RType::Server::Room::isLocked() const {
    return _is_locked;
}

/********** Getter End **********/

bool RType::Server::Room::addUser(RType::Server::Users& user) {
    if (_users.size() < MAX_CLIENT) {
        user.setInRoom(true);
        _users.push_back(user);
        return true;
    }
    return false;
}

bool RType::Server::Room::removeUser(std::string user_uuid) {
    for (auto it = _users.begin(); it != _users.end(); it++) {

        if (it->get().getUUID().compare(user_uuid) == 0) {
            it->get().setInRoom(false);
            _users.erase(it);
            return true;
        }
    }
    return false;
}

bool RType::Server::Room::userIsInRoom(std::string user_uuid) {
    for (auto it = _users.begin(); it != _users.end(); it++) {
        if (it->get().getUUID().compare(user_uuid) == 0) {
            return true;
        }
    }
    return false;
}

void RType::Server::Room::setLocked(bool locked) {
    _is_locked = locked;
}

void RType::Server::Room::setGameStarted(bool started) {
    _is_ingame = started;
}

bool RType::Server::Room::isGameStarted() const {
    return _is_ingame;
}