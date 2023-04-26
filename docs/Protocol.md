# Network Protocol

Connection:
/----------------------------------------------------------------------\
| When the client connect to the server, the client send packet with:  |
|    [type] -> "Hello"                                                 |
|    [body] -> "username"                                              |
| The server will send back a packet with:                             |
|    [type] -> "Welcome"                                               |
|    [body] -> "client uuid"                                           |
\----------------------------------------------—------—----------------/

Disconnect: This request automatically exit the client.
/-------------------------------------------------------------------------\
| When the client disconnect to the server, the client send packet with:  |
|    [type] -> "Exit"                                                     |
|    [body] -> "client username"                                          |
| The server will send back a packet with:                                |
|    [type] -> "Bye"                                                      |
|    [body] -> "client uuid"                                              |
| If the client username, not correspond to the client endpoint,          |
| the server will send back a packet with:                                |
|    [type] -> "Error"                                                    |
|    [body] -> "Wrong username"                                           |
\----------------------------------------------—------—-------------------/

Create room: This request automatically join the client uuid to the room
/-------------------------------------------------------------------------\
| When the client want to create a room, the client send packet with:     |
|    [type] -> "CreateRoom"                                               |
|    [body] -> "name room"                                                |
| The server will send back a packet with:                                |
|    [type] -> "CreateRoom"                                               |
|    [body] -> "name room|room uuid"                                      |
| If the client already in a room, the server will send back a packet     |
| with:                                                                   |
|    [type] -> "Error"                                                    |
|    [body] -> "You are already in a room"                                |
\----------------------------------------------—------—-------------------/

Room list: This request automatically send the list of room to the client
/-------------------------------------------------------------------------\
| When the client want to get the list of room, the client send packet    |
| with:                                                                   |
|    [type] -> "RoomList"                                                 |
|    [body] -> "client username"                                          |
| The server will send back a packet with:                                |
|    [type] -> "ListRoom"                                                 |
|    [body] -> "N room"                                                   |
| N room is the number of room, the server send N time the UUID of        |
| all room:                                                               |
|    [type] -> "ListRoom"                                                 |
|    [body] -> "room name|room uuid|nb user in room"                      |
| If the client username not correspond to a client endpoint,             |
| the server will send back a packet with:                                |
|    [type] -> "Error"                                                    |
|    [body] -> "Wrong username"                                           |
\----------------------------------------------—------—-------------------/

Room join: This request automatically join the client uuid to the room
/-------------------------------------------------------------------------\
| When the client want to join a room, the client send packet with:       |
|    [type] -> "JoinRoom"                                                 |
|    [body] -> "room uuid|client username"                                |
| The server will send back a packet with:                                |
|    [type] -> "JoinRoom"                                                 |
|    [body] -> "room uuid|client uuid"                                    |
| If the room is full, the server will send back a packet with:           |
|    [type] -> "RoomFull"                                                 |
|    [body] -> "room uuid"                                                |
| If the room doesn't exist, the server will send back a packet with:     |
|    [type] -> "RoomNotExist"                                             |
|    [body] -> "room uuid"                                                |
| If the client is already in the room, the server will send back a       |
| packet with:                                                            |
|    [type] -> "AlreadyInRoom"                                            |
|    [body] -> "room player uuid"                                         |
| If the client username not correspond to a client endpoint,             |
| the server will send back a packet with:                                |
|    [type] -> "Error"                                                    |
|    [body] -> "Wrong username"                                           |
\----------------------------------------------—------—-------------------/

Room leave: This request automatically leave the client uuid to the room
/-------------------------------------------------------------------------\
| When the client want to leave a room, the client send packet with:      |
|    [type] -> "LeaveRoom"                                                |
|    [body] -> "client username"                                          |
| The server will send back a packet with:                                |
|    [type] -> "LeaveRoom"                                                |
|    [body] -> "room uuid"                                                |
| If the client is not in a room, the server send packet with :           |
|    [type] -> "Error"                                                    |
|    [body] -> "You are not in a room"                                    |
| If the client username not correspond to a client endpoint,             |
| the server will send back a packet with:                                |
|    [type] -> "Error"                                                    |
|    [body] -> "Wrong username"                                           |
\----------------------------------------------—------—-------------------/

Room player ready: This request automatically set the client ready in the room
/-------------------------------------------------------------------------\
| When the client want to set ready in a room, the client send packet     |
| with:                                                                   |
|    [type] -> "Ready"                                                    |
|    [body] -> "client username"                                          |
| The server will send back a packet with:                                |
|    [type] -> "PlayerReady"                                              |
|    [body] -> "room uuid|client uuid"                                    |
| If the client is not in a room, the server send packet with :           |
|    [type] -> "Error"                                                    |
|    [body] -> "You are not in a room"                                    |
| If the client username not correspond to a client endpoint,             |
| the server will send back a packet with:                                |
|    [type] -> "Error"                                                    |
|    [body] -> "Wrong username"                                           |
| If the client is already ready, the server send packet with :           |
|    [type] -> "NotReady"                                                 |
|    [body] -> "room uuid|client uuid"                                    |
\----------------------------------------------—------—-------------------/

Room info: This request automatically send the info of the client in the room
/-------------------------------------------------------------------------\
| When the client want to get the info of a player in a room, the client  |
| send packet with:                                                       |
|    [type] -> "RoomInfo"                                                 |
|    [body] -> "client username|room uuid"                                |
| The server will send back a packet, where N is the number of player in  |
| the room:                                                               |
|    [type] -> "Info"                                                     |
|    [body] -> "N"                                                        |
| The server send N time the info of the player in the room:              |
|    [type] -> "Info"                                                     |
|    [body] -> "client uuid|client username|client ready|client is leader"|
\----------------------------------------------—------—-------------------/

Room player ready: This request automatically start game when all the player is ready in the room.
/-------------------------------------------------------------------------\
| When the client send requeste ready the server was check if everyone    |
| is ready in the room. The server send :                                 |
|    [type] -> "StartGame"                                                |
|    [body] -> "room uuid"                                                |
| Client respond in game to confirme                                      |
|    [type] -> "InGame   "                                                |
|    [body] -> "room uuid"                                                |
| If the client is in a room, the server send first wave of mob :         |
|    [type] -> "Wave"                                                     |
|    [body] -> "wave number | mob type"                                   |
\----------------------------------------------—------—-------------------/

Room player kick: This request automatically kick the client in the room.
/-------------------------------------------------------------------------\
|       /!\ Only the room creator can kick a player /!\                   | 
| To be a room creator, the client must be the first to join the room.    |
| When the client want to kick a player in a room, the client send packet |
| with:                                                                   |
|    [type] -> "Kick"                                                     |
|    [body] -> "client UUID to kick"                                      |
| The server will send back a packet to the all in room (without kicked) :|
|    [type] -> "Kicked"                                                   |
|    [body] -> "ok"                                                       |
| The server will send back a packet to the kicked player with :          |
|    [type] -> "Kicked"                                                   |
|    [body] -> "kicked"                                                   |
| If the client to kick is not in a room, the server send packet with :   |
|    [type] -> "Error"                                                    |
|    [body] -> "User not found"                                           |
| If the sender is not the room creator, the server send packet with :    |
|    [type] -> "Error"                                                    |
|    [body] -> "You are not the room creator"                             |
\----------------------------------------------—------—-------------------/

Room Lock: This request automatically lock the room.
/-------------------------------------------------------------------------\
|       /!\ Only the room creator can lock a room /!\                     |
| To be a room creator, the client must be the first to join the room.    |
| When the client want to lock a room, the client send packet with:       |
|    [type] -> "RoomLock"                                                 |
|    [body] -> "room uuid"                                                |
| The server will send back a packet to the all in room :                 |
|    [type] -> "Locked"                                                   |
|    [body] -> "0 false/1 true"                                           |
| If the sender is not the room creator, the server send packet with :    |
|    [type] -> "Error"                                                    |
|    [body] -> "You are not the room creator"                             |
\----------------------------------------------—------—-------------------/


User in game: This request is only send by the client when he is in game
/-------------------------------------------------------------------------\
| When the client is in game, the client send packet with:                |
|    [type] -> "HelloGame"                                                |
|    [body] -> "client username"                                          |
| Whith this request, the server register the client to the game entity.  |
\----------------------------------------------—------—-------------------/


Spawn: This request is only send by the server to spawn entity in game
/-------------------------------------------------------------------------\
| When the server want to spawn an entity in game, the server send packet |
| with:                                                                   |
|    [type] -> "Spawn"                                                    |
|    [body] -> "type|pos x|pos y"                                         |
| The type can be :                                                       |
|    - "player_x" -> x is player id betwen 1 and 4                        |
\----------------------------------------------—------—-------------------/