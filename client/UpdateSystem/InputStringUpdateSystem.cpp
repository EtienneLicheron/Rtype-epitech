/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** InputStringUpdateSystem
*/

#include "InputStringUpdateSystem.hpp"

void RType::Client::Scenes::InputStringUpdateSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, RType::Shared::ECS::Entity &entity, ::sf::Event &event, sf::Vector2i mouse)
{
    static std::chrono::milliseconds lastRequest = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    static int lastKey = 0;

    try
    {
        std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

        if (now.count() - lastRequest.count() < INPUT_STRING_COOLDOWN && lastKey == event.key.code)
            return;

        RType::Client::ECS::InputString &inputString = coordinator.getAttribute<RType::Client::ECS::InputString>(entity);

        if (inputString.hover == true)
        {
            RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);

            if (mouse.x < rect.value.getPosition().x || mouse.x > rect.value.getPosition().x + rect.value.getSize().x || mouse.y < rect.value.getPosition().y || mouse.y > rect.value.getPosition().y + rect.value.getSize().y)
                return;
        }

        if (event.type == sf::Event::TextEntered)
        {
            lastRequest = now;
            lastKey = event.text.unicode;

            if (event.text.unicode == 8 && inputString.text.value.getString().getSize() > 0)
                inputString.text.value.setString(inputString.text.value.getString().substring(0, inputString.text.value.getString().getSize() - 1));
            else if (inputString.text.value.getString().getSize() >= inputString.maxSize)
                return;
            else if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == ' ' || event.text.unicode == '.')
                inputString.text.value.setString(inputString.text.value.getString() + event.text.unicode);
        }
    }
    catch (...)
    {
    }
}
