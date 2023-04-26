/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Signature
*/

#ifndef __SIGNATURE_HPP__
#define __SIGNATURE_HPP__
#include "Attribute.hpp"
#include <bitset>

namespace RType
{
    namespace Shared
    {
        namespace ECS
        {
            /**
             * @brief A signature is simply a bitset of active attribute for an entity, per example, if the entity has a position and a velocity, the signature will store 2 bits to 1 <br />
             */
            typedef std::bitset<MAX_ATTRIBUTES> Signature;
        }
    }
}

#endif /* !__SIGNATURE_HPP__ */
