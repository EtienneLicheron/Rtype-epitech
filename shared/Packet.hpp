/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Packet
*/

#ifdef __GNUC__
#define packet(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define packet(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <cstdint>
#include <time.h>
#include <memory>
#include <cstring>
#include <string>
#include <vector>

namespace RType
{
    namespace Shared
    {
        /// @brief Packet to send on the network
        packet(struct Packet {
            /// @brief tick
            uint16_t _tick;
            /// @brief timestamp of the request
            time_t _timestamp;
            /// @brief type of the request
            char _type[32];
            /// @brief body of the request
            char _body[128];
        });
        // Packet& createPacket(const std::string type, const std::string body);
        RType::Shared::Packet createPacket(const std::string type, const std::string body);

        /// @brief Parse your received packet
        /// @param data
        /// @param delimitor
        /// @return vector of string containing all the data
        std::vector<std::string> parsePacket(std::string data, std::string delimitor = "|");



        enum EntityType {
            NONE = 0,
            PLAYER = 1,
            ENEMY = 2,
            BULLET = 3,
            POWERUP = 4,
            WALL = 5
        };

        struct EntityPacket {
            EntityType type;
            unsigned int id;
            float x;
            float y;
            float speed;
            int hp;
            int damage;
            int shootSpeed;
        };
        /**
         * @brief Create a Entity Packet object
         * @param type type of the entity
         * @param id id of the entity
         * @param x x position of the entity
         * @param y y position of the entity
         * @param speed speed of the entity
         * @param hp hp of the entity
         * @param damage damage of the entity
         * @param shootSpeed shoot speed of the entity
         * @return RType::Shared::EntityPacket 
         */
        RType::Shared::EntityPacket createEntityPacket(RType::Shared::EntityType type, unsigned int id, float x, float y, float speed, int hp, int damage, int shootSpeed);
        /**
         * @brief Convert an EntityPacket to a Packet
         * @param packet entity packet to convert
         * @param type type of the packet to create
         * @return RType::Shared::Packet 
         */
        RType::Shared::Packet entityPacketToPacket(RType::Shared::EntityPacket packet, std::string type);
    }
}

#endif /* !PACKET_HPP_ */
