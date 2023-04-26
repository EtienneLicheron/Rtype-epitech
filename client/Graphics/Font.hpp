/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic [WSL: Ubuntu]
** File description:
** Font
*/

#ifndef __FONT_HPP__
#define __FONT_HPP__
#include <SFML/Graphics.hpp>
#include "../Resources.hpp"

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {
            /**
             * @brief Font class to load a font
             */
            class Font
            {
                public:
                    /**
                     * @brief Construct a new Font object
                     *
                     * @param path the path of the font
                     */
                    Font(std::string path = "HelveticaNeueLTProBd.ttf");

                    /**
                     * @brief Get the Font object
                     *
                     * @return ::sf::Font&
                     */
                    sf::Font getFont();
                    ~Font();

                private:
                    sf::Font _font;
            };
        }
    }
}

#endif /* !__FONT_HPP__ */
