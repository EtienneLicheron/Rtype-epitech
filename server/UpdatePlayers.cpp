/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Update players
*/

#include "UpdatePlayers.hpp"

RType::Server::UPlayers::UPlayers()
{
    // boucle sur tout les joueurs
    if (Inputs() == SHOOT)
        this->Shoot();
    else if (Inputs() == QUIT)
        this->Quit();
    else
        this->Moove(Inputs());
    this->asShoot();
    this->isAlive();
}

RType::Server::UPlayers::INP RType::Server::UPlayers::Inputs()
{
    // if faut get les inputs du client
    // transformé en enum
}

bool RType::Server::UPlayers::Moove(INP)
{

}

bool RType::Server::UPlayers::Shoot()
{

}

bool RType::Server::UPlayers::Quit()
{

}

bool RType::Server::UPlayers::asShoot()
{

}

bool RType::Server::UPlayers::isAlive()
{

}

RType::Server::UPlayers::~UPlayers()
{
}