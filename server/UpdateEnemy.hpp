/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Update Enemy
*/

#ifndef __UPDATEENEMY_HPP__
#define __UPDATEENEMY_HPP__

namespace RType
{
    namespace Server
    {
        class UEnemy
        {
            public:
                UEnemy();
                ~UEnemy();
            private:
                bool Moove();
                bool Shoot();
                bool asShoot();
                bool isAlive();

                int id;
        };
    }
}

#endif /* !__UPDATEENEMY_HPP__ */