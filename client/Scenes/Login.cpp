/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Login
*/

#include "Login.hpp"

RType::Client::Scenes::Login::Login()
{
}

RType::Client::Scenes::Login::~Login()
{
}

void RType::Client::Scenes::Login::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::InputString>();
    _coordinator.registerAttribute<RType::Client::ECS::LoginRequest>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<LoginRenderSystem>();
}

void RType::Client::Scenes::Login::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    // Init coordinator
    _coordinator.init();

    // Attributes & System
    registerAttributes();

    // Sections
    RType::Shared::ECS::Entity _tmpEntity, _usernameEntity, _addressEntity, _portEntity;

    _tmpEntity = _coordinator.createEntity("container"); // Header
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({static_cast<float>(window.getSize().x), SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

    _tmpEntity = _coordinator.createEntity("container"); // Content LEFT 1/3
    _usernameEntity = _tmpEntity;
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {0.f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {200, 200, 200, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Username:", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::InputString>(_tmpEntity, {{RType::Client::Graphics::Text(configManager.getValue("username"), _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.5f, 0.5f}, 40).getText(), RType::Client::Graphics::Font().getFont()}, 16, true});

    _tmpEntity = _coordinator.createEntity("container"); // Content LEFT 2/3
    _addressEntity = _tmpEntity;
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {0.f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {200, 200, 200, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Address:", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::InputString>(_tmpEntity, {{RType::Client::Graphics::Text(configManager.getValue("address"), _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.5f, 0.5f}, 40).getText(), RType::Client::Graphics::Font().getFont()}, 15, true});

    _tmpEntity = _coordinator.createEntity("container"); // Content LEFT 3/3
    _portEntity = _tmpEntity;
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {0.f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f * 2.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {200, 200, 200, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Port:", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::InputString>(_tmpEntity, {{RType::Client::Graphics::Text(configManager.getValue("port"), _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.5f, 0.5f}, 40).getText(), RType::Client::Graphics::Font().getFont()}, 5, true});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 1/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 2/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});

    _tmpEntity = _coordinator.createEntity("container"); // Content RIGHT 3/3
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, static_cast<float>((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f)}, {window.getSize().x * .7f, static_cast<float>(SECTION_HEADER_HEIGHT + (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f * 2.f)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Connect", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::LoginRequest>(_tmpEntity, {_usernameEntity, _addressEntity, _portEntity});

    // Rectangle of transition
    // _tmpEntity = _coordinator.createEntity();
    // _coordinator.addAttribute<RType::Shared::ECS::Position>(_tmpEntity, {0.0f, 0.0f});
    // _coordinator.addAttribute<RType::Shared::ECS::Size>(_tmpEntity, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    // _coordinator.addAttribute<RType::Shared::ECS::Color>(_tmpEntity, RType::Shared::ECS::Color{0, 0, 0});
    // _coordinator.addAttribute<RType::Shared::ECS::Opacity>(_tmpEntity, {255});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Login::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Login::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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

            // Login Request Update
            if (_coordinator.hasAttribute<RType::Client::ECS::LoginRequest>(entity))
                _loginRequestUpdateSystem.update(deltatime, _coordinator, entity, lastClick, _mouse, menu, configManager);

            // Hover Update
            if (_coordinator.hasAttribute<RType::Client::ECS::Hover>(entity))
                _hoverUpdateSystem.update(deltatime, _coordinator, entity, _mouse);
        }
        catch (...)
        {
        }
    }

    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::Login::LoginRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
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
