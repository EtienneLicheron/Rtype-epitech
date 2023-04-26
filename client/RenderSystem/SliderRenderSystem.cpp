/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SliderRenderSystem
*/

#include "SliderRenderSystem.hpp"
#include <iostream>

void RType::Client::Scenes::SliderRenderSystem::update(::sf::RenderWindow &window, RType::Client::ECS::Slider &slider)
{
    ::sf::Vector2i mousePosition = ::sf::Mouse::getPosition(window);
    float cursorPosition = (slider.position.x - slider.width / 20) + (slider.width / slider.maxValue) * slider.value;

    // BAR
    _tmpBar = ::sf::RectangleShape(::sf::Vector2f(slider.width, slider.height));
    _tmpBar.setFillColor({slider.barColor.r, slider.barColor.g, slider.barColor.b, slider.barColor.a});
    _tmpBar.setPosition(slider.position);

    // CURSOR
    _tmpCursor = ::sf::RectangleShape(::sf::Vector2f(static_cast<float>(slider.width / 10), static_cast<float>(slider.height * 1.2f))); // 1.2f to scale it 20% bigger
    _tmpCursor.setPosition(cursorPosition, slider.position.y - (slider.height * 0.1f));

    // HOVER ACTIVE, IDLE CURSOR
    if (_tmpBar.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || _tmpCursor.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        _tmpCursor.setFillColor({slider.cursorHoverColor.r, slider.cursorHoverColor.g, slider.cursorHoverColor.b, slider.cursorHoverColor.a});
        if (::sf::Mouse::isButtonPressed(::sf::Mouse::Left)) {
            slider.value = static_cast<int>((mousePosition.x - slider.position.x) / (slider.width / slider.maxValue));
            if (slider.value < 0)
                slider.value = 0;
            if (slider.value > slider.maxValue)
                slider.value = slider.maxValue;
            // create a popup with the current value
            ::sf::RectangleShape _tmpPopup = ::sf::RectangleShape(_tmpCursor.getSize());
            _tmpPopup.setFillColor({slider.popupColor.r, slider.popupColor.g, slider.popupColor.b, slider.popupColor.a});
            _tmpPopup.setPosition(_tmpCursor.getPosition().x, _tmpCursor.getPosition().y - _tmpCursor.getSize().y - 10);
            // create a text with the current value
            ::sf::Font font = ::sf::Font();
            font.loadFromFile(RType::Client::Resources::getPath(Resources::Font, "HelveticaNeueLTProBd.ttf"));
            ::sf::Text _tmpText = ::sf::Text(std::to_string(slider.value), font, _tmpCursor.getSize().y * 0.7f);
            _tmpText.setFillColor({slider.popupTextColor.r, slider.popupTextColor.g, slider.popupTextColor.b, slider.popupTextColor.a});
            _tmpText.setPosition(_tmpPopup.getPosition().x + _tmpPopup.getSize().x / 2 - _tmpText.getGlobalBounds().width / 2, (_tmpPopup.getPosition().y + _tmpPopup.getSize().y / 2 - _tmpText.getGlobalBounds().height / 2) - _tmpCursor.getSize().y * 0.2f);
            // draw the popup and the text
            window.draw(_tmpPopup);
            window.draw(_tmpText);
        }
    } else
        _tmpCursor.setFillColor({slider.cursorColor.r, slider.cursorColor.g, slider.cursorColor.b, slider.cursorColor.a});

    // DRAW
    window.draw(_tmpBar);
    window.draw(_tmpCursor);
}
