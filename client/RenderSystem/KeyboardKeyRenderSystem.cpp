/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** KeyboardKeyRenderSystem
*/

#include "KeyboardKeyRenderSystem.hpp"

void RType::Client::Scenes::KeyboardKeyRenderSystem::update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::KeyboardKey &key)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    init(key);
    if (key.autoPress) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - key.clock).count() > 500) {
            key.pressed = !key.pressed;
            key.clock = std::chrono::system_clock::now();
        }
    }
    else {
        sf::Keyboard::Key sfkey = sf::Keyboard::Unknown;
        switch (key.character) {
            case ' ':
                sfkey = sf::Keyboard::Space;
                break;
            default:
                sfkey = static_cast<sf::Keyboard::Key>(key.character - 65);
                break;
        }
        if ((mousePos.x >= key.position.x && mousePos.x <= key.position.x + key.rectangle.getSize().x && mousePos.y >= key.position.y && mousePos.y <= key.position.y + key.rectangle.getSize().y) \
        || sf::Keyboard::isKeyPressed(sfkey)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sfkey))
                key.pressed = true;
            else
                key.pressed = false;
        }
        else
            key.pressed = false;
    }
    if (!key.pressed) {
        key.rectangle.setPosition(key.position.x, key.position.y);
        key.text.setPosition(key.position.x + (key.height - key.text.getGlobalBounds().width) / 2, key.position.y + ((key.height * 0.8) - key.text.getGlobalBounds().height) / 2);
    }
    else {
        key.rectangle.setPosition(key.position.x, key.position.y + 9);
        key.text.setPosition(key.position.x + (key.height - key.text.getGlobalBounds().width) / 2, key.position.y + ((key.height * 0.8) - key.text.getGlobalBounds().height) / 2 + 9);
    }
    window.draw(key.shadow);
    window.draw(key.rectangle);
    window.draw(key.text);
}

void RType::Client::Scenes::KeyboardKeyRenderSystem::init(RType::Client::ECS::KeyboardKey &key)
{
    if (key.rectangle.getPosition().x == key.position.x && key.rectangle.getPosition().y == key.position.y)
        return; // Already initialized

    key.rectangle = ::sf::RectangleShape(::sf::Vector2f(key.height, key.height));
    key.rectangle.setSize(key.character == ' ' ? sf::Vector2f(key.height * 5, key.height) : sf::Vector2f(key.height, key.height));
    key.rectangle.setPosition(key.position);
    key.rectangle.setFillColor({ 51, 51, 51, 255 });
    key.rectangle.setOutlineColor({ 68, 68, 68, 255 });
    key.rectangle.setOutlineThickness(1);

    key.shadow = ::sf::RectangleShape(::sf::Vector2f(key.height + 2, key.height));
    key.shadow.setSize(key.character == ' ' ? sf::Vector2f(key.height * 5 + 2, key.height) : sf::Vector2f(key.height + 2, key.height));
    key.shadow.setPosition(key.position.x - 1, key.position.y + 10);
    key.shadow.setFillColor({ 34, 34, 34, 255 });

    key.font = ::sf::Font();
    key.font.loadFromFile(RType::Client::Resources::getPath(Resources::Font, "HelveticaNeueLTProBd.ttf"));
    key.text = ::sf::Text(key.character, key.font, key.height - 20);

    key.text.setFillColor(sf::Color::White);
    key.text.setPosition(key.position.x + (key.height - key.text.getGlobalBounds().width) / 2, key.position.y + ((key.height * 0.8) - key.text.getGlobalBounds().height) / 2);

    key.clock = std::chrono::system_clock::now();
}
