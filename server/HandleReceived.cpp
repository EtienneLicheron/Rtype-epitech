/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** HandleReceived
*/

#include "ServerUDP.hpp"
#include <algorithm>
namespace RType
{
    namespace Server
    {
        void UDPServer::handleHello(ClientPacket cltPck)
        {
            bool test = true;
            RType::Server::Users &client = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            for (auto &cli : _clients)
            {
                if (cli.getUsername().compare(packet._body) == 0 && cli.getUUID().compare(client.getUUID()) != 0)
                {
                    send(RType::Shared::createPacket("Error", "Username already taken"), client.getEndpoint());
                    test = false;
                }
            }
            client.setUsername(packet._body);
            if (test)
                send(RType::Shared::createPacket("Welcome", client.getUUID()), client.getEndpoint());
        }

        void UDPServer::handleExit(ClientPacket cltPck)
        {
            RType::Server::Users client = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            if (client.getUsername().compare(packet._body) == 0)
            {
                if (client.isInRoom())
                {
                    RType::Server::Room &room = getRoomByUserUUID(client.getUUID());
                    room.removeUser(client.getUUID());
                    if (room.getNbUsers() == 0)
                        removeRoom(room.getUUID());
                    for (auto it = _games.begin(); it != _games.end(); it++)
                    {
                        if (it->get()->getRoomInGame().getNbUsers() == 0)
                            _games.erase(it);
                    }
                }
                send(RType::Shared::createPacket("Bye", client.getUUID()), client.getEndpoint());
                removeClient(client.getUUID());
            }
            else
                send(RType::Shared::createPacket("Error", "Wrong username"), client.getEndpoint());
        }

        void UDPServer::handleCreateRoom(ClientPacket cltPck)
        {
            RType::Server::Users &client = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            std::string name(packet._body);

            std::cout << "DEBUG CREATE ROOM" << std::endl;
            client.print();
            if (!client.isInRoom())
            {
                client.setInRoom(true);
                RType::Server::Room room(name, client);
                _rooms.emplace_back(std::move(room));
                client.print();
                std::string sendBody(room.getName());
                sendBody.append("|");
                sendBody.append(room.getUUID());
                send(RType::Shared::createPacket("CreateRoom", sendBody), client.getEndpoint());
            }
            else
                send(RType::Shared::createPacket("Error", "You are already in a room"), client.getEndpoint());
        }

        void UDPServer::handleRoomList(ClientPacket cltPck)
        {
            RType::Server::Users client = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            std::string name(packet._body);
            client.print();
            if (name.compare(client.getUsername()) == 0)
            {
                send(RType::Shared::createPacket("ListRoom", std::to_string(_rooms.size())), client.getEndpoint());
                std::string sendBody;
                for (auto &room : _rooms)
                {
                    if (room.isLocked() || room.isGameStarted() ) {
                        continue;
                    } else {
                        sendBody.append(room.getName() + "|" + room.getUUID() + "|" + std::to_string(room.getNbUsers()));
                        send(RType::Shared::createPacket("ListRoom", sendBody), client.getEndpoint());
                        sendBody.clear();
                    }
                }
            }
            else
                send(RType::Shared::createPacket("Error", "Wrong username"), client.getEndpoint());
        }

        void UDPServer::handleJoinRoom(ClientPacket cltPck)
        {
            RType::Server::Users &client = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            std::string body(packet._body);
            std::string roomUUID(body.substr(0, body.find('|')));
            std::string username(body.substr(body.find('|') + 1, body.size()));
            if (username.compare(client.getUsername()) == 0)
            {
                if (!client.isInRoom())
                {
                    for (auto &room : _rooms)
                    {
                        if (room.getUUID().compare(roomUUID) == 0)
                        {
                            if (room.addUser(client))
                            {
                                std::string sendbody(roomUUID + "|" + client.getUUID());
                                send(RType::Shared::createPacket("JoinRoom", sendbody), client.getEndpoint());
                                client.setInRoom(true);

                                /*DEBUG*/
                                for (auto user : room.getUser())
                                {
                                    // user.print();
                                    user.get().print();
                                }
                                return;
                            }
                            else
                            {
                                send(RType::Shared::createPacket("RoomFull", roomUUID), client.getEndpoint());
                                return;
                            }
                        }
                    }
                    send(RType::Shared::createPacket("RoomNotExist", roomUUID), client.getEndpoint());
                }
                else
                    send(RType::Shared::createPacket("AlreadyInRoom", getRoomByUserUUID(client.getUUID()).getUUID()), client.getEndpoint());
            }
            else
                send(RType::Shared::createPacket("Error", "Wrong username"), client.getEndpoint());
        }

        void UDPServer::handleLeaveRoom(ClientPacket cltPck)
        {
            RType::Server::Users &user = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            if (user.getUsername().compare(packet._body) == 0)
            {
                if (user.isInRoom())
                {
                    RType::Server::Room &room = getRoomByUserUUID(user.getUUID());
                    if (room.getOwnerUUID().compare(user.getUUID()) == 0)
                    {
                        for (auto &usr : room.getUser())
                        {
                            if (usr.get().getUUID().compare(user.getUUID()) != 0)
                            {
                                send(RType::Shared::createPacket("Kicked", "Kicked"), usr.get().getEndpoint());
                                usr.get().setInRoom(false);
                                usr.get().setReady(false);
                                room.removeUser(usr.get().getUUID());
                            }
                        }
                    }
                    user.setInRoom(false);
                    user.setReady(false);
                    room.removeUser(user.getUUID());
                    send(RType::Shared::createPacket("LeaveRoom", room.getUUID()), user.getEndpoint());
                    if (room.getNbUsers() == 0)
                    {
                        removeRoom(room.getUUID());
                    }
                    else
                    {
                        int nbUser = room.getNbUsers();
                        std::vector<std::reference_wrapper<Users>> vusers = room.getUser();
                        sendToAllInRoom(RType::Shared::createPacket("Info", std::to_string(nbUser)), room);
                        for (int i = 0; i < nbUser; i++)
                        {
                            sendToAllInRoom(RType::Shared::createPacket("Info", vusers[i].get().getUUID() + "|" + vusers[i].get().getUsername() + "|" + std::to_string(vusers[i].get().isReady())), room);
                        }
                    }
                }
                else
                    send(RType::Shared::createPacket("Error", "You are not in a room"), user.getEndpoint());
            }
            else
                send(RType::Shared::createPacket("Error", "Wrong username"), user.getEndpoint());
        }

        void UDPServer::handleReady(ClientPacket cltPck)
        {
            RType::Server::Users &user = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            if (user.getUsername().compare(packet._body) == 0)
            {
                if (user.isInRoom())
                {
                    RType::Server::Room &room = getRoomByUserUUID(user.getUUID());
                    bool ready = true;
                    if (user.isReady())
                    {
                        ready = false;
                        user.setReady(ready);
                        std::cout << "\n\n NOT READY" << std::endl;
                        user.print();
                        send(RType::Shared::createPacket("NotReady", room.getUUID()), user.getEndpoint());
                        return;
                    }
                    else
                    {
                        user.setReady(ready);
                        std::cout << "\n\n READY" << std::endl;
                        user.print();
                        send(RType::Shared::createPacket("PlayerReady", room.getUUID()), user.getEndpoint());
                    }
                    bool allReady = true;
                    for (auto &usr : room.getUser())
                    {
                        usr.get().getUUID().compare(user.getUUID()) == 0 ? usr.get().setReady(ready) : usr.get().setReady(usr.get().isReady());
                        if (!allReady)
                            allReady = false;
                        else
                            allReady = usr.get().isReady();
                        usr.get().print();
                    }
                    if (allReady)
                    {
                        room.setGameStarted(true);
                        sendToAllInRoom(RType::Shared::createPacket("GameStart", room.getUUID()), room);
                    }
                }
                else
                    send(RType::Shared::createPacket("Error", "You are not in a room"), user.getEndpoint());
            }
            else
                send(RType::Shared::createPacket("Error", "Wrong username"), user.getEndpoint());
        }

        void UDPServer::handleInGame(ClientPacket cltPck)
        {
            // user who send the packet
            RType::Server::Users &user = cltPck.second;
            // packet
            RType::Shared::Packet packet = cltPck.first;
            // room of the user who send the packet / the room where the game is
            RType::Server::Room &room = getRoomByUserUUID(user.getUUID());

            for (auto &game : _games)
                if (game->getRoomInGame().getUUID().compare(room.getUUID()) == 0)
                    return;
            std::string port = "";
            while (true)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1024, 65535);
                port.assign(std::to_string(dis(gen)));
                try
                {
                    asio::ip::udp::socket socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), std::stoi(port)));
                    // RType::Server::Game game(socket, room);
                    socket.close();
                    std::shared_ptr<RType::Server::Game> game = std::make_shared<RType::Server::Game>(port, room, _debug_mode);
                    _games.push_back(std::move(game));
                    sendToAllInRoom(RType::Shared::createPacket("GamePort", port), room);
                    break;
                }
                catch (...)
                {
                    continue;
                }
            }
        }

        void UDPServer::handleRoomInfo(ClientPacket cltPck)
        {
            RType::Server::Users &user = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            std::string body(packet._body);
            if (user.getUsername().compare(body.substr(0, body.find("|"))) == 0)
            {
                Room room = getRoomByUserUUID(user.getUUID());
                if (room.getUUID().compare(body.substr(body.find("|") + 1)) == 0)
                {
                    int nbUser = room.getNbUsers();
                    std::string leader(room.getOwnerUUID());
                    std::vector<std::reference_wrapper<Users>> users = room.getUser();
                    sendToAllInRoom(RType::Shared::createPacket("Info", std::to_string(nbUser) + "|" + std::to_string(room.isLocked())), room);
                    for (int i = 0; i < nbUser; i++)
                    {
                        int isLeader = (users[i].get().getUUID().compare(leader) == 0) ? true : false;
                        sendToAllInRoom(RType::Shared::createPacket("Info", users[i].get().getUUID() + "|" + users[i].get().getUsername() + "|" + std::to_string(users[i].get().isReady()) + "|" + std::to_string(isLeader)), room);
                    }
                }
            }
        }

        void UDPServer::handleKick(ClientPacket cltPck)
        {
            RType::Server::Users &user = cltPck.second; 
            RType::Shared::Packet packet = cltPck.first;
            std::string toKickUUID(packet._body);
            RType::Server::Room &room = getRoomByUserUUID(user.getUUID());

            if (room.getOwnerUUID().compare(user.getUUID()) == 0)
            {
                for (auto &usr : room.getUser())
                {
                    if (usr.get().getUUID().compare(toKickUUID) == 0)
                    {
                        send(RType::Shared::createPacket("Kicked", "Kicked"), usr.get().getEndpoint());
                        usr.get().setInRoom(false);
                        usr.get().setReady(false);
                        room.removeUser(usr.get().getUUID());
                        sendToAllInRoom(RType::Shared::createPacket("Kicked", usr.get().getUsername()), room);
                        return;
                    }
                }
                send(RType::Shared::createPacket("Error", "User not found"), user.getEndpoint());
            }
            else
            {
                send(RType::Shared::createPacket("Error", "You are not the owner of the room"), user.getEndpoint());
            }
        }

        void UDPServer::handleRoomLock(ClientPacket cltPck)
        {
            RType::Server::Users &user = cltPck.second;
            RType::Shared::Packet packet = cltPck.first;
            RType::Server::Room &room = getRoomByUserUUID(user.getUUID());

            if (room.getOwnerUUID().compare(user.getUUID()) == 0 && room.getUUID().compare(packet._body) == 0) {
                room.setLocked(!room.isLocked());
                sendToAllInRoom(RType::Shared::createPacket("Locked", std::to_string(room.isLocked())), room);
            } else {
                send(RType::Shared::createPacket("Error", "You are not the room creator"), user.getEndpoint());
            }
        }
    }
}