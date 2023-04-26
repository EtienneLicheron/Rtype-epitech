/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundRenderSystem
*/

#include "SoundRenderSystem.hpp"

void RType::Client::Scenes::SoundRenderSystem::update(::sf::RenderWindow &window, RType::Client::ECS::Sound &sound)
{
    if (sound.value == nullptr)
        initSound(sound);
    if (sound.playing) {
        sound.value->setVolume(sound.volume);
        sound.value->setPlayingOffset(::sf::seconds(0.0f));
        sound.value->play();
        sound.playing = false;
    }
}

void RType::Client::Scenes::SoundRenderSystem::initSound(RType::Client::ECS::Sound &sound)
{
    sound.buffer = std::make_shared<::sf::SoundBuffer>();
    sound.buffer->loadFromFile(RType::Client::Resources::getPath(Resources::Sound, sound.fileName));
    sound.value = std::make_shared<::sf::Sound>(*sound.buffer.get());
}
