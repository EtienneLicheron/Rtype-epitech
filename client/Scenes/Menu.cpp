/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

RType::Client::Scenes::Menu::Menu()
{
}

RType::Client::Scenes::Menu::~Menu()
{
}

void RType::Client::Scenes::Menu::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::SwitchScene>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<MenuRenderSystem>();
}

void RType::Client::Scenes::Menu::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    // Init coordinator
    _coordinator.init();

    // Attributes & System
    registerAttributes();

    // Sections
    RType::Shared::ECS::Entity _tmpEntity;

    _tmpEntity = _coordinator.createEntity("container"); // Header
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({static_cast<float>(window.getSize().x), SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType - Main menu", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

    _tmpEntity = _coordinator.createEntity("container"); // Content
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>(window.getSize().y - SECTION_HEADER_HEIGHT)}, {0.f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 1/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 0.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {244, 55, 49, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Play", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"RoomList"});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 2/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 1.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 172, 56, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Settings", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"Settings"});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 3/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 2.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("How to play", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"HowToPlay"});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Menu::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Menu::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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

void RType::Client::Scenes::Menu::MenuRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
{
    (void)deltatime;

    window.clear(sf::Color::White);

    for (auto &entity : coordinator.getEntities())
    {
        try
        {
            RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);

            // Render BackGround
            window.draw(rect.value);

            // Render Hover
            if (coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                window.draw(coordinator.getAttribute<RType::Client::ECS::Hover>(entity).rect.value);

            // Render Text
            if (coordinator.hasAttribute<RType::Client::ECS::Text>(entity))
                _textRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Text>(entity));

            // Render Border
            _borderRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Border>(entity), rect.value.getPosition(), rect.value.getSize());
        }
        catch (...)
        {
        }
    }
}
