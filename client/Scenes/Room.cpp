/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

#include "Room.hpp"

RType::Client::Scenes::Room::Room()
{
}

RType::Client::Scenes::Room::~Room()
{
}

void RType::Client::Scenes::Room::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::ServerRequest>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<RoomRenderSystem>();
}

void RType::Client::Scenes::Room::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
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
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

    _tmpEntity = _coordinator.createEntity("container"); // Content
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>(window.getSize().y - SECTION_HEADER_HEIGHT)}, {0.f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 1/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {244, 55, 49, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Back", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::ServerRequest>(_tmpEntity, {"LeaveRoom", "", _tmpEntity});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 2/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 3/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f * 2.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Ready", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::ServerRequest>(_tmpEntity, {"Ready", "", _tmpEntity});

    menu.sendGetRoomInfo();

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Room::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Room::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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

    try
    {
        for (auto &entity : _coordinator.getEntities())
        {
            // Hover Update
            if (_coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                _hoverUpdateSystem.update(deltatime, _coordinator, entity, _mouse);

            // Server Request Update
            if (_coordinator.hasAttribute<RType::Client::ECS::ServerRequest>(entity))
                _serverRequestUpdateSystem.update(deltatime, _coordinator, entity, lastClick, menu, _mouse);
        }
    }
    catch (...)
    {
    }

    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::Room::RoomRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
{
    window.clear(sf::Color::White);

    try
    {
        for (auto &entity : coordinator.getEntities())
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
    }
    catch (...)
    {
    }
}
