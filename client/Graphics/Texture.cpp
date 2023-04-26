/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Texture
*/

#include "Texture.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            Texture::Texture(std::string path, bool repeated)
            {
                _texture.loadFromFile(RType::Client::Resources::getPath(Resources::Sprite, path));
                _texture.setRepeated(repeated);
            }

            sf::Texture &Texture::getTexture()
            {
                return _texture;
            }

            Texture::~Texture()
            {
            }
        }
    }
}
