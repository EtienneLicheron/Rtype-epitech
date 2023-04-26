/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Settings
*/

#include "Settings.hpp"

RType::Client::Scenes::Settings::Settings()
{
}

RType::Client::Scenes::Settings::~Settings()
{
}

void RType::Client::Scenes::Settings::registerAttributes()
{
    _coordinator.registerAttribute<RType::Client::ECS::RectangleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Border>();
    _coordinator.registerAttribute<RType::Client::ECS::Hover>();
    _coordinator.registerAttribute<RType::Client::ECS::Text>();
    _coordinator.registerAttribute<RType::Client::ECS::SwitchScene>();
    _coordinator.registerAttribute<RType::Client::ECS::Position>();
    _coordinator.registerAttribute<RType::Client::ECS::Color>();
    _coordinator.registerAttribute<RType::Client::ECS::InputString>();
    _coordinator.registerAttribute<RType::Client::ECS::Slider>();
    _coordinator.registerAttribute<RType::Client::ECS::SaveAction>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<SettingsRenderSystem>();
}

void RType::Client::Scenes::Settings::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    // Init coordinator
    _coordinator.init();

    // Register attributes
    registerAttributes();

    // Entities
    RType::Shared::ECS::Entity _tmpEntity, menuMusicVolumeTmp, gameMusicVolumeTmp, gameSoundsVolumeTmp;

    _tmpEntity = _coordinator.createEntity("header"); // Header
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({static_cast<float>(window.getSize().x), SECTION_HEADER_HEIGHT}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("RType - Settings", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds(), {0.025f, 0.5f}, 80).getText(), RType::Client::Graphics::Font().getFont()});

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
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Back", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"Menu"});

    _tmpEntity = _coordinator.createEntity("rthree"); // Right-column - 3/3 (Back button)
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .3f, (window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f}, {window.getSize().x * 0.7f, SECTION_HEADER_HEIGHT + ((window.getSize().y - SECTION_HEADER_HEIGHT) / 3.f) * 2.f}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, false, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 72, 213, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("How to play", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SwitchScene>(_tmpEntity, {"HowToPlay"});

    _tmpEntity = _coordinator.createEntity("settings-name"); // Settings - Menu music volume
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {window.getSize().x * .35f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 0)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Menu music volume", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.getAttribute<RType::Client::ECS::Text>(_tmpEntity).value.setCharacterSize(40);

    _tmpEntity = _coordinator.createEntity("settings-name"); // Settings - Game music volume
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {window.getSize().x * .35f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 1)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Game music volume", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.getAttribute<RType::Client::ECS::Text>(_tmpEntity).value.setCharacterSize(40);

    _tmpEntity = _coordinator.createEntity("settings-name"); // Settings - Game sound volume
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {window.getSize().x * .35f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 2)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Game sound volume", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.getAttribute<RType::Client::ECS::Text>(_tmpEntity).value.setCharacterSize(40);

    menuMusicVolumeTmp = _tmpEntity = _coordinator.createEntity("settings-value-menuMusicVolume"); // Settings - Menu music volume value
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {0.0f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 0)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, false, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Slider>(_tmpEntity, {/* value */ std::stoi(configManager.getValue("menuMusicVolume")), /* height */ 30, /* width */ static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .9f), /* position*/ {/*x*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().x + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .05f + 6),
                                                                                                                                                                                                                                                                                                          /*y*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().y + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().y * .35f)},
                                                                       /* maxValue */ 100, /* minValue */ 0});

    gameMusicVolumeTmp = _tmpEntity = _coordinator.createEntity("settings-value-gameMusicVolume"); // Settings - Game music volume value
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {0.0f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 1)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, false, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Slider>(_tmpEntity, {/* value */ std::stoi(configManager.getValue("gameMusicVolume")), /* height */ 30, /* width */ static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .9f), /* position*/ {/*x*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().x + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .05f + 6),
                                                                                                                                                                                                                                                                                                          /*y*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().y + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().y * .35f)},
                                                                       /* maxValue */ 100, /* minValue */ 0});

    gameSoundsVolumeTmp = _tmpEntity = _coordinator.createEntity("settings-value-gameSoundsVolume"); // Settings - Game sound volume value
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .35f, SECTION_HEADER_HEIGHT / 1.5f}, {0.0f, SECTION_HEADER_HEIGHT + ((SECTION_HEADER_HEIGHT / 1.5f) * 2)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, false, true, true, false, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Slider>(_tmpEntity, {/* value */ std::stoi(configManager.getValue("gameSoundsVolume")), /* height */ 30, /* width */ static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .9f), /* position*/ {/*x*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().x + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().x * .05f + 6),
                                                                                                                                                                                                                                                                                                           /*y*/ _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getPosition().y + static_cast<int>(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getSize().y * .35f)},
                                                                       /* maxValue */ 100, /* minValue */ 0});

    _tmpEntity = _coordinator.createEntity("save-btn"); // Settings - Save button
    _coordinator.addAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity, {RType::Client::Graphics::RectangleShape({window.getSize().x * .7f, SECTION_HEADER_HEIGHT}, {0, static_cast<float>(window.getSize().y - SECTION_HEADER_HEIGHT)}).getRectangleShape()});
    _coordinator.addAttribute<RType::Client::ECS::Border>(_tmpEntity, {12, true, true, true, true, {0, 0, 0, 255}});
    _coordinator.addAttribute<RType::Client::ECS::Hover>(_tmpEntity, {{RType::Client::Graphics::RectangleShape(_coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value, {0, 172, 56, 0}).getRectangleShape()}, HOVER_TRANSITION});
    _coordinator.addAttribute<RType::Client::ECS::Text>(_tmpEntity, {RType::Client::Graphics::Text("Save", _coordinator.getAttribute<RType::Client::ECS::RectangleShape>(_tmpEntity).value.getGlobalBounds()).getText(), RType::Client::Graphics::Font().getFont()});
    _coordinator.addAttribute<RType::Client::ECS::SaveAction>(_tmpEntity, {menuMusicVolumeTmp, gameMusicVolumeTmp, gameSoundsVolumeTmp});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Settings::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Settings::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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

            // Save Action Update
            if (_coordinator.hasAttribute<RType::Client::ECS::SaveAction>(entity))
                _saveActionUpdateSystem.update(deltatime, _coordinator, entity, lastClick, _mouse, configManager);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    _renderSystem->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::Settings::SettingsRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window)
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

            // Border Render
            if (coordinator.hasAttribute<RType::Client::ECS::RectangleShape>(entity))
            {
                RType::Client::ECS::RectangleShape rect = coordinator.getAttribute<RType::Client::ECS::RectangleShape>(entity);
                _borderRenderSystem.update(deltatime, window, coordinator.getAttribute<RType::Client::ECS::Border>(entity), rect.value.getPosition(), rect.value.getSize());
            }

            // Slider Render
            if (coordinator.hasAttribute<RType::Client::ECS::Slider>(entity))
                _sliderRenderSystem.update(window, coordinator.getAttribute<RType::Client::ECS::Slider>(entity));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
