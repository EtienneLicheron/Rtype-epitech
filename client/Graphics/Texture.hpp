/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Texture
*/

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include <SFML/Graphics.hpp>
#include "../Resources.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief Texture class to load a texture
             */
            class Texture
            {
                public:
                    /**
                     * @brief Construct a new Texture object
                     *
                     * @param path the path of the texture
                     * @param repeated if the texture is repeated
                     */
                    Texture(std::string path, bool repeated = false);

                    /**
                     * @brief Get the Texture object
                     *
                     * @return sf::Texture&
                     */
                    sf::Texture &getTexture();
                    ~Texture();

                private:
                    sf::Texture _texture;
            };
        }
    }
}

#endif /* !__TEXTURE_HPP__ */
