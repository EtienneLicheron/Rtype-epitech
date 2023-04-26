/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Utils
*/


#include "Utils.hpp"

std::ostream& operator<<(std::ostream &out, RType::Shared::Packet const &p) {
    return out << p._tick << ";" << p._timestamp << ";" << p._type << ";" << p._body << ";";
}