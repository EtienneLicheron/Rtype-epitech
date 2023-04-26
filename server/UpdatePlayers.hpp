/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Update players
*/

#ifndef __UPDATEPLAYERS_HPP__
#define __UPDATEPLAYERS_HPP__

namespace RType
{
    namespace Server
    {
        class UPlayers
        {
            public:
                UPlayers();
                ~UPlayers();
            private:
                enum INP {
                    UP,
                    DOWN,
                    LEFT,
                    RIGHT,
                    SHOOT,
                    QUIT
                };
                INP Inputs();
                bool Moove(INP);
                bool Shoot();
                bool Quit();
                bool asShoot();
                bool isAlive();
                int id;
        };
    }
}

#endif /* !__UPDATEPLAYERS_HPP__ */