/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** PlayerRenderSystem
*/

#include "PlayerRenderSystem.hpp"

namespace RType {
    namespace Client {
        namespace Scenes {
            void PlayerRenderSystem::update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::Sprite &sprite, RType::Client::ECS::Text &text)
            {
                sprite.value.setTexture(sprite.texture);
                text.value.setFont(text.font);
                text.value.setPosition(sprite.value.getPosition().x - 65, sprite.value.getPosition().y - 35);
                window.draw(sprite.value);
                window.draw(text.value);
            }
        }
    }
}
