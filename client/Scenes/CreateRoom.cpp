/*CreateRoom
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CreateRoom
*/

#include "CreateRoom.hpp"

RType::Client::Scenes::CreateRoom::CreateRoom()
{
}

RType::Client::Scenes::CreateRoom::~CreateRoom()
{
}

void RType::Client::Scenes::CreateRoom::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::SwitchScene>();
    _coordinator.registerAttribute<RType::Client::ECS::ServerRequest>();
    _coordinator.registerAttribute<RType::Client::ECS::InputString>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<CreateRoomRenderSystem>();
}

void RType::Client::Scenes::CreateRoom::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    // Init coordinator
    _coordinator.init();

    // Attributes & System
    registerAttributes();

    // Sections
    RType::Shared::ECS::Entity _tmpEntity, _tempEntityLink;

    _tmpEntity = _coordinator.createEntity("container"); // Header
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({static_cast<float>(window.getSize().x), SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType - Create room", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

    _tmpEntity = _coordinator.createEntity("container"); // Content
    _tempEntityLink = _tmpEntity;
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * 0.7f, static_cast<float>(window.getSize().y) - SECTION_HEADER_HEIGHT}, {window.getSize().x * 0.3f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Enter Room Name:", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.1f, 0.4f}).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::InputString>(_tmpEntity, {{RType::Client::Graphics::Text("", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.1f, 0.5f}, 40).getText(), RType::Client::Graphics::Font().getFont()}, 16, false});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 1/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * 0.3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {0.f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 0.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {244, 55, 49, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Back", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"RoomList"});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 2/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * 0.3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {0.f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 1.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Right-column - 3/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * 0.3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {0.f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 2.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Create", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::ServerRequest>(_tmpEntity, {"CreateRoom", "", _tempEntityLink});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::CreateRoom::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::CreateRoom::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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
            // Input String Update
            if (_coordinator.hasAttribute<RType::Client::ECS::InputString>(entity))
                _inputStringUpdateSystem.update(deltatime, _coordinator, entity, _event, _mouse);

            // Hover Update
            if (_coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                _hoverUpdateSystem.update(deltatime, _coordinator, entity, _mouse);

            // Switch Scene Update
            if (_coordinator.hasAttribute<RType::Client::ECS::SwitchScene>(entity))
                _switchSceneUpdateSystem.update(deltatime, _coordinator, entity, lastClick, currentScene, _mouse);

            // Server Request Update
            if (_coordinator.hasAttribute<RType::Client::ECS::ServerRequest>(entity))
                _serverRequestUpdateSystem.update(deltatime, _coordinator, entity, lastClick, menu, _mouse);
        }
        catch (...)
        {
        }
    }

    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::CreateRoom::CreateRoomRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
{
    (void)deltatime;

    window.clear(sf::Color::White);

    for (auto &entity : coordinator.getEntities())
    {
        try
        {
            RType::Client::ECS::RectangleShape &rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);

            // Render Rectangle
            window.draw(rect.value);

            // Render Hover
            if (coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                window.draw(coordinator.getAttribute<RType::Client::ECS::Hover>(entity).rect.value);

            // Render Text
            if (coordinator.hasAttribute<RType::Client::ECS::Text>(entity))
                _textRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Text>(entity));

            // Input String Render
            if (coordinator.hasAttribute<RType::Client::ECS::InputString>(entity))
                _textRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::InputString>(entity).text);

            // Render Border
            _borderRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Border>(entity), rect.value.getPosition(), rect.value.getSize());
        }
        catch (...)
        {
        }
    }
}
