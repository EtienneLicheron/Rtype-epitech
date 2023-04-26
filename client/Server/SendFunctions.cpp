/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** SendFunctions
*/

#include "MenuUDP.hpp"

namespace RType {
    namespace Client {
        void MenuUDP::sendLogin(std::string username) {
            std::string type = "Hello";
            send(RType::Shared::createPacket(type, username));
        }

        void MenuUDP::sendDisconnect() {
            send(RType::Shared::createPacket("Exit", _username));
        }

        void MenuUDP::sendNewRoom(std::string roomName) {
            if (!_isInRoom) {
                std::string body(roomName);
                send(RType::Shared::createPacket("CreateRoom", body));
            }
        }

        void MenuUDP::sendRoomList() {
            send(RType::Shared::createPacket("RoomList", _username));
        }

        void MenuUDP::sendJoinRoom(std::string roomUUID) {
            if (!_isInRoom) {
                std::string body(roomUUID + "|" + _username);
                // body.append("|");
                // body.append(_username);
                send(RType::Shared::createPacket("JoinRoom", body));
            }
        }

        void MenuUDP::sendLeaveRoom() {
            if (_isInRoom) {
                send(RType::Shared::createPacket("LeaveRoom", _username));
                _isInRoom = false;
            }
        }

        void MenuUDP::sendPlayerReady() {
            if (_isInRoom) {
                send(RType::Shared::createPacket("Ready", _username));
            }
        }

        void MenuUDP::sendPlayerInGame() {
            send(RType::Shared::createPacket("InGame", _username));
        }

        void MenuUDP::sendGetRoomInfo() {
            send(RType::Shared::createPacket("RoomInfo", _username + "|" + _roomUUID));
        }

        void MenuUDP::sendKickPlayer(std::string toKickUUID) {
            send(RType::Shared::createPacket("Kick", toKickUUID));
        }

        void MenuUDP::sendRoomLock() {
            send(RType::Shared::createPacket("Lock", _roomUUID));
        }

        // void MenuUDP::sendMove(std::string direction) {
        //     send(RType::Shared::createPacket("Move", direction));
        // }
    }
}
