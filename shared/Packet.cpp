/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Packet
*/

#include "Packet.hpp"
#include <iostream>

RType::Shared::Packet RType::Shared::createPacket(const std::string type, const std::string body)
{
    RType::Shared::Packet packet;

    packet._tick = 0;
    packet._timestamp = time(NULL);
    std::memset(packet._type, 0, 32);
    for (int i = 0; i < type.length(); i++)
        packet._type[i] = type.at(i);
    std::memset(packet._body, 0, 128);
    for (int i = 0; i < body.length(); i++)
        packet._body[i] = body.at(i);
    return packet;
}

std::vector<std::string> RType::Shared::parsePacket(std::string data, std::string delimitor)
{
    std::vector<std::string> args;
    size_t pos = 0;
    std::string token;
    while ((pos = data.find(delimitor)) != std::string::npos)
    {
        token = data.substr(0, pos);
        args.push_back(token);
        data.erase(0, pos + delimitor.size());
    }
    args.push_back(data);
    return args;
}

RType::Shared::EntityPacket RType::Shared::createEntityPacket(RType::Shared::EntityType type, unsigned int id, float x, float y, float speed, int hp, int damage, int shootSpeed) {
    RType::Shared::EntityPacket packet;

    packet.type = type;
    packet.id = id;
    packet.x = x;
    packet.y = y;
    packet.speed = speed;
    packet.hp = hp;
    packet.damage = damage;
    packet.shootSpeed = shootSpeed;
    return packet;
}

RType::Shared::Packet RType::Shared::entityPacketToPacket(RType::Shared::EntityPacket packet, std::string type) {
    RType::Shared::Packet newPacket;

    newPacket._tick = 0;
    newPacket._timestamp = time(NULL);
    std::memset(newPacket._type, 0, 32);
    std::memset(newPacket._body, 0, 128);
    std::string body = std::to_string(packet.type) + "|" + std::to_string(packet.id) + "|" + std::to_string(packet.x) + "|" + std::to_string(packet.y) + "|" + std::to_string(packet.speed) + "|" + std::to_string(packet.hp) + "|" + std::to_string(packet.damage) + "|" + std::to_string(packet.shootSpeed);
    for (int i = 0; i < type.length(); i++)
        newPacket._type[i] = type.at(i);
    for (int i = 0; i < body.length(); i++)
        newPacket._body[i] = body.at(i);
    return newPacket;
}