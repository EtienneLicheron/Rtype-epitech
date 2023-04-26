/*
** EPITECH PROJECT, 2022
** B-CPP-500 - RType
** File description:
** main
*/

#include "ServerUDP.hpp"

int main(int ac, char **av)
{
    try {
        bool debug = false;
        if (ac == 3) {
            if (std::string(av[2]) == "-d" || std::string(av[1]) == "-d")
                debug = true;
        } else if (ac != 2) {
            std::cerr << "Usage: server <port> [optionnal: -d for debug]" << std::endl;
            return (1);
        }
        RType::Server::UDPServer server(av[1], debug);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
