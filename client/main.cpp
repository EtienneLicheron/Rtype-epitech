/*
** EPITECH PROJECT, 2022
** B-CPP-500 - RType
** File description:
** main
*/

#include "Application.hpp"
#include "Server/MenuUDP.hpp"

int main(int ac, char **av)
{
    try
    {
        if (ac != 4 && ac != 1)
        {
            std::cerr << "Usage: ./client [host] [port] [username]" << std::endl;
            return 84;
        }

        std::string host = "254.254.254.254";
        if (ac == 4)
            host = (((std::string)("localhost")).compare(av[1]) == 0) ? "127.0.0.1" : av[1];
        RType::Client::Application app(host, ac == 1 ? 9999 : std::stoi(av[2]), ac == 1 ? "Unknow" : av[3]);
        app.run();
        return (0);
    }
    catch (const RType::Shared::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "The program will now exit." << std::endl;
        return (84);
    }
    catch (...)
    {
        std::cerr << "An unknown error occured." << std::endl;
        std::cerr << "The program will now exit." << std::endl;
        return (84);
    }
}
