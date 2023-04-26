/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Game
*/

#include "Game.hpp"

RType::Client::Scenes::Game::Game()
{
}

RType::Client::Scenes::Game::~Game()
{
}

void RType::Client::Scenes::Game::registerAttribute()
{
    _coordinator.registerAttribute<RType::Client::ECS::Sprite>();
    _coordinator.registerAttribute<RType::Shared::ECS::Speed>();
    _coordinator.registerAttribute<RType::Client::ECS::DisplayName>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Shared::ECS::Velocity>();
    _coordinator.registerAttribute<RType::Client::ECS::Music>();
    _coordinator.registerAttribute<RType::Client::ECS::Sound>();
    // Register the system
    _renderSystem = _coordinator.registerSystem<GameRenderSystem>();
}

void RType::Client::Scenes::Game::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    std::stringstream ss;
    float gameMusicVolume = 100.0f;
    float gameSoundsVolume = 100.0f;
    std::string tmpConf = "";
    tmpConf.assign(configManager.getValue("gameMusicVolume"));
    if (!tmpConf.empty())
        gameMusicVolume = std::stof(tmpConf);
    tmpConf.assign(configManager.getValue("gameSoundsVolume"));
    if (!tmpConf.empty())
        gameSoundsVolume = std::stof(tmpConf);
    // Init coordinator
    _coordinator.init();

    // Register Attributes & System
    registerAttribute();

    // Sections
    RType::Shared::ECS::Entity _tmpEntity;

    _tmpEntity = _coordinator.createEntity("background");
    _coordinator.addAttribute<RType::Client::ECS::Sprite>(_tmpEntity, {RType::Client::Graphics::Sprite().getSprite(), RType::Client::Graphics::Texture("background.png", true).getTexture()});
    _coordinator.addAttribute<RType::Shared::ECS::Speed>(_tmpEntity, {.1f});

    _tmpEntity = _coordinator.createEntity("menuMusic");
    _coordinator.addAttribute<RType::Client::ECS::Music>(_tmpEntity, {"Game.ogg", gameMusicVolume});

    _tmpEntity = _coordinator.createEntity("laserShoot");
    _coordinator.addAttribute<RType::Client::ECS::Sound>(_tmpEntity, {"Laser.wav", gameSoundsVolume});

    _tmpEntity = _coordinator.createEntity("enemyDestroyed");
    _coordinator.addAttribute<RType::Client::ECS::Sound>(_tmpEntity, {"Explosion.wav", gameSoundsVolume});


    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Game::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Game::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
{
    if (!_loaded)
        return;

    while (window.pollEvent(_event))
    {
        if (_event.type == ::sf::Event::Closed)
        {
            window.close();
            return;
        }
        for (auto &entity : _coordinator.getEntities())
        {
            RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
            if (entityType.value == _playerID)
                _playerUpdateSystem.update(deltatime, _coordinator, entity, _event, menu);
        }
    }
    for (auto &entity : _coordinator.getEntities())
    {
        try
        {
            RType::Shared::ECS::EntityType &entityType = _coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);

            if (entityType.value.find("bullet_") != std::string::npos)
                _projectileUpdateSystem.update(deltatime, _coordinator, entity, window, menu);
            else if (entityType.value == "background")
                _backgroundUpdateSystem.update(deltatime, _coordinator, entity, window);
        }
        catch (...)
        {
        }
    }
    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::Game::GameRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
{
    (void)deltatime;

    window.clear(sf::Color::Black);

    for (auto &entity : coordinator.getEntities())
    {
        try
        {
            RType::Shared::ECS::EntityType &entityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
            if (coordinator.hasAttribute<RType::Client::ECS::Music>(entity)) {
                RType::Client::ECS::Music &music = coordinator.getAttribute<RType::Client::ECS::Music>(entity);
                _musicRenderSystem.update(window, music);
            }
            if (coordinator.hasAttribute<RType::Client::ECS::Sound>(entity)) {
                RType::Client::ECS::Sound &sound = coordinator.getAttribute<RType::Client::ECS::Sound>(entity);
                _soundRenderSystem.update(window, sound);
            }
            if (entityType.value == "player_1" || entityType.value == "player_2" || entityType.value == "player_3" || entityType.value == "player_4")
            {
                RType::Client::ECS::Sprite &sprite = coordinator.getAttribute<RType::Client::ECS::Sprite>(entity);
                RType::Client::ECS::Text &text = coordinator.getAttribute<RType::Client::ECS::Text>(entity);
                _playerRenderSystem.update(deltatime, window, sprite, text);
            }
            else
            {
                _spriteRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Sprite>(entity));
            }

        }
        catch (...)
        {
        }
    }
}
