/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicRenderSystem
*/

#include "MusicRenderSystem.hpp"

void RType::Client::Scenes::MusicRenderSystem::update(::sf::RenderWindow &window, RType::Client::ECS::Music &music)
{
    bool hasPlaylist = music.currentSong >= 0;

    if (!music.hasToPlay) {
        if (music.value->getStatus() == ::sf::Music::Playing)
            music.value->stop();
        return;
    }
    if (music.currentSong == -42)
        hasPlaylist = initPlaylist(music);
    music.value->setVolume(music.volume);
    if (!hasPlaylist) {
        if (music.value->getStatus() == ::sf::Music::Status::Stopped)
            music.value->play();
        music.value->setLoop(true);
    } else {
        if (music.value->getStatus() == ::sf::Music::Status::Stopped)
            updatePlaylist(music);
        music.value->setLoop(false);
    }
}

bool RType::Client::Scenes::MusicRenderSystem::initPlaylist(RType::Client::ECS::Music &music)
{
    std::string path = Resources::getPath(Resources::Music, music.fileName.substr(0, music.fileName.find_last_of(".")) + ".txt");
    std::ifstream file(path); // ouvrir les timecodes pour la playlist
    std::string line;

    if (music.value == nullptr)
        music.value = std::make_shared<::sf::Music>();
    music.value->openFromFile(RType::Client::Resources::getPath(Resources::Music, music.fileName));
    music.value->setLoop(true);
    if (!file.is_open()) {
        music.currentSong = -1;
        return false;
    }
    while (std::getline(file, line))
        music.playlist.push_back(line);
    file.close();
    updatePlaylist(music);
    return true;
}

void RType::Client::Scenes::MusicRenderSystem::updatePlaylist(RType::Client::ECS::Music &music)
{
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, music.playlist.size() - 1);
    music.currentSong = distribution(generator);
    std::stringstream ss;
    std::string minutes_s = music.playlist[music.currentSong].substr(0, music.playlist[music.currentSong].find(":"));
    std::string seconds_s = music.playlist[music.currentSong].substr(music.playlist[music.currentSong].find(":") + 1, music.playlist[music.currentSong].size());
    int minutes = 0;
    int seconds = 0;
    ss << minutes_s;
    ss >> minutes;
    ss.clear();
    ss << seconds_s;
    ss >> seconds;
    music.value->setPlayingOffset(::sf::seconds(minutes * 60 + seconds));
    music.value->play();
}
