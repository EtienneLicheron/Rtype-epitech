/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** KeyboardKey
*/

#include "KeyboardKey.hpp"
#include <iostream>

namespace RType {
    namespace Client {
        namespace Graphics {

            KeyboardKey::KeyboardKey(const char character, ::sf::Vector2f position, const int height, const bool autoPress) : _character(character), _position(position), _height(height), _autoPress(autoPress) {
                _rectangle = ::sf::RectangleShape(::sf::Vector2f(_height, _height));
                _rectangle.setSize(_character == ' ' ? sf::Vector2f(_height * 3, _height) : sf::Vector2f(_height, _height));
                _rectangle.setPosition(_position);
                _rectangle.setFillColor({ 51, 51, 51, 255 });
                _rectangle.setOutlineColor({ 68, 68, 68, 255 });
                _rectangle.setOutlineThickness(1);

                _shadow = ::sf::RectangleShape(::sf::Vector2f(_height + 2, _height));
                _shadow.setPosition(_position.x - 1, _position.y + 10);
                _shadow.setFillColor({ 34, 34, 34, 255 });

                _font = sf::Font();
                _font.loadFromFile(RType::Client::Resources::getPath(Resources::Font, "HelveticaNeueLTProBd.ttf"));
                _text = ::sf::Text(character, _font, TEXT_SIZE);
                _text.setFillColor(sf::Color::White);
                _text.setPosition(_position.x + (_height - _text.getGlobalBounds().width) / 2, _position.y);
                _clock = std::chrono::system_clock::now();
            }

            KeyboardKey::~KeyboardKey() {
            }

            bool KeyboardKey::display(::sf::RenderWindow &window) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (_autoPress) {
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _clock).count() > 500) {
                        _pressed = !_pressed;
                        _clock = std::chrono::system_clock::now();
                    }
                } else {
                    if (mousePosition.x >= _position.x && mousePosition.x <= _position.x + _rectangle.getSize().x && mousePosition.y >= _position.y && mousePosition.y <= _position.y + _rectangle.getSize().y && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        _pressed = true;
                    else
                        _pressed = false;
                }

                if (_pressed) {
                    _rectangle.setPosition(_position.x, _position.y + 9);
                    _text.setPosition(_position.x + (_height - _text.getGlobalBounds().width) / 2, _position.y + 9);
                } else {
                    _rectangle.setPosition(_position.x, _position.y);
                    _text.setPosition(_position.x + (_height - _text.getGlobalBounds().width) / 2, _position.y);
                }
                window.draw(_shadow);
                window.draw(_rectangle);
                window.draw(_text); // CRASH
                return (_pressed);
            }

        }
    }
}
