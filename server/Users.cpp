/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Users
*/

#include "Users.hpp"

RType::Server::Users::Users(asio::ip::udp::endpoint endpoint, std::string username) : _uuid(RType::Shared::UUID::generate()), _endpoint(endpoint), _username(username) {
    _in_room = false;
    _ready = false;
}

RType::Server::Users::~Users()
{
}
