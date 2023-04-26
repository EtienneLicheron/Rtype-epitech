/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Font
*/

#include "Font.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            Font::Font(std::string path)
            {
                _font.loadFromFile(RType::Client::Resources::getPath(Resources::Font, path));
            }

            sf::Font Font::getFont()
            {
                return (_font);
            }

            Font::~Font()
            {
            }
        }
    }
}
