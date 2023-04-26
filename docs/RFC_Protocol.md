Request for comment: ???                                            
Category: Documentation
Epitech Montpellier

                                                                    Sebastien Phelip
                                                                    Laurent Amat
                                                                    Benjamin Vic
                                                                    Etienne Licheron
                                                                    Adrien Zobiri
                                                                    November 2022


                        RType: Third year epitech project

Abstract

    This document describes the protocol used by the RType game. The RType it's a game
    who is a clone of the famous game R-Type. The game is a multiplayer game who is
    played by 1 to 4 players. The server can host several games at the same time.


Table of Contents

    1. Introduction .................................................... Line 44
    2. Architecture .................................................... Line 49
    3. Protocol ........................................................ Line 63
        3.1. Menu ...................................................... Line 74
            3.1.A. Connection .......................................... Line 76
            3.1.B. Disconnection ....................................... Line 92
            3.1.C. Create room ......................................... Line 104
            3.1.D. List room ........................................... Line 118
            3.1.E. Join room ........................................... Line 132
            3.1.F. Leave room .......................................... Line 153
            3.1.G. Player ready ........................................ Line 168
            3.1.H. Room info ........................................... Line 187
            3.1.I. Kick player ......................................... Line 197
            3.1.J. Room lock ........................................... Line 217
            3.1.K. Debug mode .......................................... Line 232
        3.2. Game ...................................................... Line 243
            3.2.A. Start game .......................................... Line 245
            3.2.B. Hello Game .......................................... Line 258
            3.2.C. Game Wave ........................................... Line 268

1. Introduction

    The goal of this project is to create a game who is a clone of the famous game R-Type (1987). This project is made with C++ and external library like SFML for graphic or ASIO for network.


2. Architecture

    This project have 2 binaries, the server and the client.

    The server is the main binary, it's not a graphical binary, it's a console binary.
    You can't interact with the server, it's only a server who host the game.
    The server is multi-threaded, it's mean that the server can host several games at the same time. 
    The server handle every client by a thread. When a room start a game (a room it's a lobby where the players wait for the game to start), the server create a new thread for the game, and he create new socket to handle the game, where only client in game can communicate with this socket.

    The client it's a graphical binary, it's mean that the client have a graphical interface. The client can connect to the server and play the game. The client can create a room, join a room, play the game, and disconnect from the server.

    This two binaries has some common code, like the ECS (Entity Component System) or the protocol. 


3. Protocol

    The newtork protocol used it's a UDP. All the packets are send in binary. 
    The packet have a Type, and Body. The type it's a char[32] and the body it's a char[128].

    /!\ If the body is write in capital letter, it's mean that it's a variable (ex: CLIENT_USERNAME it's username of client).
    If in the body you see something like: "ROOM_NAME|ROOM_UUID", it's mean that the body is composed of 2 variables, the first it's the name of the room, and the second it's the uuid of the room.
    All the variable who contain IS, it's mean that it's a boolean (true or false).
    (ex: ROOM_IS_LOCKED it's mean that the room is locked or not).


    3.1 Menu

        3.1.A. Connection

            When client want to connect to server it's send:
                [Client] -> [Server] : Type: "Hello", Body: "CLIENT_USERNAME"

            If the server accept the connection, it's send:
                [Server] -> [Client] : Type: "Welcome", Body: "CLIENT_UUID"

            If the server refuse the connection (if username is already taken), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Username already taken"
            
            If the client can't connect to the server (if ip or port is wrong):
                The client automatically come in the menu to connect to the server.
                The client need to enter the ip and the port of the server, and this username.
        

        3.1.B. Disconnection

            When the client want to disconnect from the server, it's send:
                [Client] -> [Server] : Type: "Exit", Body: "CLIENT_USERNAME"
            
            If the server accept the disconnection, it's send:
                [Server] -> [Client] : Type: "Bye", Body: "CLIENT_UUID"

            If the server refuse the disconnection (if username is not found or not correspond), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Wrong username"


        3.1.C. Create room
        
            When client create room it's automatically become the room leader.

            When the client want to create a room, it's send:
                [Client] -> [Server] : Type: "CreateRoom", Body: "ROOM_NAME"

            If the server accept the creation of the room, it's send:
                [Server] -> [Client] : Type: "CreateRoom", Body: "ROOM_NAME|ROOM_UUID"

            If the server refuse the creation of the room (if the user is already in room), it's send:
                [Server] -> [Client] : Type: "Error", Body: "You are already in a room"
        

        3.1.D. List room

            When the client want to list the room, it's send:
                [Client] -> [Server] : Type: "RoomList", Body: "CLIENT_USERNAME"

            If the server accept the list of the room, it's send:
                [Server] -> [Client] : Type: "ListRoom", Body: "NUMBER_ROOM"
            The server send a packet for each room, it's send:
                [Server] -> [Client] : Type: "ListRoom", Body: "ROOM_NAME|ROOM_UUID|NB_PLAYER"

            If the server refuse the list of the room (if the user is not found or not correspond), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Wrong username"


        3.E. Join room

            When the client want to join a room, it's send:
                [Client] -> [Server] : Type: "JoinRoom", Body: "ROOM_UUID|CLIENT_USERNAME"
            
            If the server accept the join of the room, it's send:
                [Server] -> [Client] : Type: "JoinRoom", Body: "ROOM_UUID|CLIEN_UUID"

            If the server refuse the join of the room (if the room is full), it's send:
                [Server] -> [Client] : Type: "RoomFull", Body: "ROOM_UUID"

            If the server refuse the join of the room (if the room is not found), it's send:
                [Server] -> [Client] : Type: "RoomNotExist", Body: "ROOM_UUID"

            If the server refuse the join of the room (if the user is already in room), it's send:
                [Server] -> [Client] : Type: "AlreadyInRoom", Body: "ROOM_UUID_WHERE_PLAYER_IS"

            If the server refuse the join of the room (if the username not correspond), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Wrong username"


        3.1.F. Leave room

            When the client want to leave a room, it's send:
                [Client] -> [Server] : Type: "LeaveRoom", Body: "CLIENT_USERNAME"
            
            If the server accept the leave of the room, it's send:
                [Server] -> [Client] : Type: "LeaveRoom", Body: "ROOM_UUID"

            If the server refuse the leave of the room (if the user is not in the room), it's send:
                [Server] -> [Client] : Type: "Error", Body: "You are not in a room"

            If the server refuse the leave of the room (if the username not correspond), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Wrong username"

        
        3.1.G. Player ready

            When the client want to be ready, it's send:
                [Client] -> [Server] : Type: "Ready", Body: "CLIENT_USERNAME"

            If the server accept the ready of the player, it's send:
                [Server] -> [Client] : Type: "PlayerReady", Body: "ROOM_UUID|CLIENT_UUID"
                or if the player is already ready:
                [Server] -> [Client] : Type: "NotReady", Body: "ROOM_UUID|CLIENT_UUID"

            If the server refuse the ready of the player (if the user is not in the room), it's send:
                [Server] -> [Client] : Type: "Error", Body: "You are not in a room"

            If the server refuse the ready of the player (if the username not correspond), it's send:
                [Server] -> [Client] : Type: "Error", Body: "Wrong username"

            If all players in room are ready the server send GameStart packet (see 3.2.A. Game start)

            
        3.1.H. Room info

            This request is send when client join a room, or when a player join or leave the room.

            When the client need to actualize the room info, the server send:
                [Server] -> [Client] : Type: "Info", Body: "NUMBER_PLAYER|ROOM_IS_LOCKED"
                The server send a packet for each player in the room, it's send:
                [Server] -> [Client] : Type: "Info", Body: "PLAYER_UUID|PLAYER_USERNAME|PLAYER_IS_READY|PLAYER_IS_ROOM_LEADER"

        
        3.1.I. Kick player

            /!\ This request is only send by the room leader.
            To be a room leader see [3.1.C]Create room.

            When the client want to kick a player, it's send:
                [Client] -> [Server] : Type: "Kick", Body: "PLAYER_UUID_TO_KICK"

            If the server accept the kick of the player, it's send (to all player in the room except the kicked player):
                [Server] -> [Client] : Type: "Kick", Body: "PLAYER_USERNAME"
            and it's send to the kicked player:
                [Server] -> [Client] : Type: "Kicked", Body: "kicked"

            If the server refuse the kick of the player (if the user is not in the room), it's send:
                [Server] -> [Client] : Type: "Error", Body: "User not found"

            If the server refuse the kick of the player (if the user is not the room leader), it's send:
                [Server] -> [Client] : Type: "Error", Body: "You are not the room leader"


        3.1.J. Room lock

            /!\ This request is only send by the room leader.
            To be a room leader see [3.1.C]Create room.

            When the client want to lock the room, it's send:
                [Client] -> [Server] : Type: "RoomLock", Body: "ROOM_UUID"

            If the server accept the lock of the room, it's send:
                [Server] -> [Client] : Type: "Locked", Body: "ROOM_IS_LOCKED"

            If the server refuse the lock of the room (if the user is not the leader), it's send:
                [Server] -> [Client] : Type: "Error", Body: "You are not the room leader"

        
        3.1.K. Debug mode
        
                This request is automatically send by the server, when it run in debug mode.
                The debug mode is activated when the server is run with the argument "-d".
                With this mode, the server and the client print all information about the packets.

                The server send:
                    [Server] -> [Client] : Type: "Debug", Body: ""



    3.2. Game

        3.2.A. Start Game

            When all players in the room are ready, the server send to all clients in room:
                [Server] -> [Client] : Type: "GameStart", Body: "ROOM_UUID"

            When the client receive this packet, it's start the game. And it's send:
                [Client] -> [Server] : Type: "InGame", Body: "ROOM_UUID"

            Here the server create a new socket for the game, and send to all clients in room:
                [Server] -> [Client] : Type: "GamePort", Body: "GAME_SOCKET_PORT"
                When client received this packet it's connect to the game socket. Now the client send new request to the game socket (see [3.2.B.] HelloGame).


        3.2.B. HelloGame

            When a client is connected to the game socket, it's send:
                [Client] -> [Server] : Type: "HelloGame", Body: "CLIENT_USERNAME"

                The server set the information for game entity ([TODO SEE ECS HERE])

            The server send back to all client in room (for each client):
                [Server] -> [Client] : Type: "Spawn", Body: "PLAYER_NUM|PLAYER_POS_X|PLAYER_POS_Y"

        3.2.C. Game Wave

                When the server want to send a wave to all clients in room, it's send:
                    [Server] -> [Client] : Type: "Wave", Body: "// TODO"

                When the client receive this packet, it's spawn a wave entity ([TODO SEE ECS HERE]).