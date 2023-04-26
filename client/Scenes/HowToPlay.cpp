/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** HowToPlay
*/

#include "HowToPlay.hpp"

RType::Client::Scenes::HowToPlay::HowToPlay()
{
}

RType::Client::Scenes::HowToPlay::~HowToPlay()
{
}

void RType::Client::Scenes::HowToPlay::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::SwitchScene>();
    _coordinator.registerAttribute<RType::Client::ECS::Position>();
    _coordinator.registerAttribute<RType::Client::ECS::Color>();
    _coordinator.registerAttribute<RType::Client::ECS::KeyboardKey>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<HTPRenderSystem>();
}

void RType::Client::Scenes::HowToPlay::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    // Init coordinator
    _coordinator.init();

    // Register attributes
    registerAttributes();

    // Entities
    RType::Shared::ECS::Entity _tmpEntity;

    _tmpEntity = _coordinator.createEntity("header"); // Header
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({static_cast<float>(window.getSize().x), SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType - How to play", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

    _tmpEntity = _coordinator.createEntity("container"); // Content
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>(window.getSize().y - SECTION_HEADER_HEIGHT)}, {0.f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("rone"); // Right-column - 1/3 (Play button)
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 0.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {244, 55, 49, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Play", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"RoomList"});

    _tmpEntity = _coordinator.createEntity("rtwo"); // Right-column - 2/3 (Settings button)
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 1.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 172, 56, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Settings", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"Settings"});

    _tmpEntity = _coordinator.createEntity("rthree"); // Right-column - 3/3 (Back button)
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 2.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Back", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"Menu"});

    _tmpEntity = _coordinator.createEntity("content-text"); // Content
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {{"The goal of the game is to\ndestroy all the ennemies,\nyou can do that by shooting\nthem with your spaceship\nand avoid their bullets.\nPress      to move up\nPress      to move right\nPress      to move down\nPress      to move left\nPress                   to shoot with your weapon.", RType::Client::Graphics::Font().getFont()}, RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::Position>(_tmpEntity, {20, SECTION_HEADER_HEIGHT + 10});

    _tmpEntity = _coordinator.createEntity("up"); // Up key
    _coordinator.addAttribute<RType::Client::ECS::KeyboardKey>(_tmpEntity, {'Z', {175, 479}, 45});

    _tmpEntity = _coordinator.createEntity("right"); // Right key
    _coordinator.addAttribute<RType::Client::ECS::KeyboardKey>(_tmpEntity, {'D', {175, 539}, 45});

    _tmpEntity = _coordinator.createEntity("down"); // Down key
    _coordinator.addAttribute<RType::Client::ECS::KeyboardKey>(_tmpEntity, {'S', {175, 599}, 45});

    _tmpEntity = _coordinator.createEntity("left"); // Left key
    _coordinator.addAttribute<RType::Client::ECS::KeyboardKey>(_tmpEntity, {'Q', {175, 659}, 45});

    _tmpEntity = _coordinator.createEntity("shoot"); // Shoot key
    _coordinator.addAttribute<RType::Client::ECS::KeyboardKey>(_tmpEntity, {' ', {175, 719}, 45});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::HowToPlay::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::HowToPlay::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
{
    if (!_loaded)
        return;

    _mouse = sf::Mouse::getPosition(window);

    while (window.pollEvent(_event))
    {
        if (_event.type == ::sf::Event::Closed)
        {
            window.close();
            return;
        }
    }

    for (auto &entity : _coordinator.getEntities())
    {
        try
        {
            // Hover Update
            if (_coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                _hoverUpdateSystem.update(deltatime, _coordinator, entity, _mouse);

            // Switch Scene Update
            if (_coordinator.hasAttribute<RType::Client::ECS::SwitchScene>(entity))
                _switchSceneUpdateSystem.update(deltatime, _coordinator, entity, lastClick, currentScene, _mouse);
        }
        catch (...)
        {
        }
    }
    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::HowToPlay::HTPRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
{
    (void)deltatime;

    window.clear(sf::Color::White);
    for (auto &entity : coordinator.getEntities())
    {
        try
        {
            RType::Shared::ECS::EntityType &entityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity);
            // RectangleShape Render
            if (coordinator.hasAttribute<RType::Client::ECS::RectangleShape>(entity))
                window.draw(coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity).value);

            // Render Hover
            if (coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                window.draw(coordinator.getAttribute<RType::Client::ECS::Hover>(entity).rect.value);

            // Render Text
            if (coordinator.hasAttribute<RType::Client::ECS::Text>(entity) && entityType.value != "content-text")
                _textRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Text>(entity));

            // Render Content Text
            if (coordinator.hasAttribute<RType::Client::ECS::Text>(entity) && entityType.value == "content-text")
            {
                RType::Client::ECS::Text &text = coordinator.getAttribute<RType::Client::ECS::Text>(entity);
                RType::Client::ECS::Position &position = coordinator.getAttribute<RType::Client::ECS::Position>(entity);
                text.font.loadFromFile(RType::Client::Resources::getPath(Resources::Font, "HelveticaNeueLTProBd.ttf"));
                text.value.setFont(text.font);
                text.value.setPosition({position.x, position.y});
                text.value.setCharacterSize(50);
                text.value.setFillColor(sf::Color::Black);
                window.draw(text.value);
            }
            // Border Render
            if (coordinator.hasAttribute<RType::Client::ECS::RectangleShape>(entity))
            {
                RType::Client::ECS::RectangleShape rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);
                _borderRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Border>(entity), rect.value.getPosition(), rect.value.getSize());
            }

            // Keyboards Key
            if (coordinator.hasAttribute<RType::Client::ECS::KeyboardKey>(entity))
                _keyboardKeyRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::KeyboardKey>(entity));
        }
        catch (...)
        {
        }
    }
}
