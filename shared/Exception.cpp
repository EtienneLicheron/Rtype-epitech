/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Exception
*/

#include "Exception.hpp"

namespace RType {
    namespace Shared {
        Exception::Exception(std::string message) : _message(message)
        {
        }

        const char* Exception::what() const throw() {
            return (_message.c_str());
        };

    }
}
