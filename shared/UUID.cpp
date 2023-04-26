/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UUID
*/

#include "UUID.hpp"

std::string RType::Shared::UUID::generate()
{
    static std::random_device rd; // obtain a random number from hardware
    static std::mt19937 gen(rd()); // Mersenne twister algorithm
    static std::uniform_int_distribution<> dis(0, 15); // generate numbers between 0 and 15
    static std::uniform_int_distribution<> dis2(8, 11); // generate numbers between 8 and 11
    std::stringstream ss;
    int i = 0;

    ss << std::hex; // set hex mode
    for (i = 0; i < 8; i++) // generate 8 numbers
        ss << dis(gen);
    ss << "-";
    for (i = 0; i < 4; i++) // generate 4 numbers
        ss << dis(gen);
    ss << "-4";
    for (i = 0; i < 3; i++) // generate 3 numbers (the previous is a 4, because UUID version 4)
        ss << dis(gen);
    ss << "-";
    ss << dis2(gen); // generate a number between 8 and 11
    for (i = 0; i < 3; i++) // generate 3 numbers
        ss << dis(gen);
    ss << "-";
    for (i = 0; i < 12; i++) // generate 12 numbers
        ss << dis(gen);
    return (ss.str());
}

bool RType::Shared::UUID::isValid(std::string uuid)
{
    if (uuid.length() != 36) // UUID length is 36
        return (false);
    if (uuid[8] != '-' || uuid[13] != '-' || uuid[18] != '-' || uuid[23] != '-') // check if the 4 '-' are in the right place
        return (false);
    if (uuid[14] != '4') // check if the version is 4
        return (false);
    for (int i = 0; i < 36; i++) { // check if the string is hexadecimal
        if (i == 8 || i == 13 || i == 18 || i == 23)
            continue;
        if (uuid[i] < '0' || (uuid[i] > '9' && uuid[i] < 'A') || (uuid[i] > 'F' && uuid[i] < 'a') || uuid[i] > 'f')
            return (false);
    }
    return (true);
}
