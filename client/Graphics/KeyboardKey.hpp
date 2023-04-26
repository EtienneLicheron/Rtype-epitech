/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** KeyboardKey
*/

#ifndef __KEYBOARDKEY_HPP__
    #define __KEYBOARDKEY_HPP__
    #include <SFML/Graphics.hpp>
    #include "../Resources.hpp"
    #define TEXT_SIZE _height - 20

namespace RType
{
    namespace Client
    {
        namespace Graphics
        {

            /**
             * @brief This attribute is used to represent a keyboard key (that can be pressed or not)
             */
            class KeyboardKey
            {
                public:
                    /**
                     * @brief Construct a new Keyboard Key object
                     *
                     * @param character the character of the key
                     * @param position the position of the key
                     * @param height the height of the key
                     * @param autoPress if the key is auto pressed
                     */
                    KeyboardKey(const char character, ::sf::Vector2f position, const int height = 60, const bool autoPress = false);
                    ~KeyboardKey();
                    /**
                     * @brief Display the keyboard key
                     *
                     * @param window The window to display the keyboard key
                     * @return true If the keyboard key is pressed
                     * @return false If the keyboard key is not pressed
                     */
                    bool display(::sf::RenderWindow &window);

                private:
                    char _character;
                    ::sf::Vector2f _position;
                    int _height;
                    bool _autoPress;
                    bool _pressed;
                    ::sf::RectangleShape _rectangle;
                    ::sf::RectangleShape _shadow;
                    ::sf::Text _text;
                    ::sf::Font _font;
                    /**
                     * @brief Internal clock used to auto press the key (if _autoPress is true)
                     */
                    std::chrono::time_point<std::chrono::system_clock> _clock;
            };

        }
    }
}

#endif /* !__KEYBOARDKEY_HPP__ */
