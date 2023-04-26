/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Exception
*/

#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__
#include <string>
#include <exception>

namespace RType
{
    namespace Shared
    {
        /**
         * @brief Exception class to throw custom exceptions
         */
        class Exception
        {
        public:
            /**
             * @brief Throw an exception with a custom message
             *
             * @param message Custom message to display
             */
            Exception(std::string message);

            /**
             * @brief Get the message of the exception
             *
             * @return const char* The message of the exception
             */
            const char *what() const throw();

        private:
            /**
             * @brief The message of the exception
             */
            const std::string _message;
        };
    }
}

#endif /* !__EXCEPTION_HPP__ */
