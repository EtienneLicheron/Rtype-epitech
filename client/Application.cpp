/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Application
*/

#include "Application.hpp"
#include <csignal>

RType::Client::Application *RType::Client::Application::instance;

RType::Client::Application::Application(std::string host, unsigned short port, ::std::string username) : _deltatime(0), _window(::sf::VideoMode(1600, 900), "R-Type", ::sf::Style::Titlebar | ::sf::Style::Close, ::sf::ContextSettings(0, 0, 8, 2, 0)), _bootScene("Login"), _tmpScene("Splash"), _currentScene("Splash"), _menu(*this, asio::ip::make_address(host), port, username), _configManager(), _lastClick(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())), _coordinator()
{
    _scenes["Splash"] = std::make_unique<RType::Client::Scenes::Splash>();
    _scenes["Login"] = std::make_unique<RType::Client::Scenes::Login>();
    _scenes["Menu"] = std::make_unique<RType::Client::Scenes::Menu>();
    _scenes["HowToPlay"] = std::make_unique<RType::Client::Scenes::HowToPlay>();
    _scenes["Settings"] = std::make_unique<RType::Client::Scenes::Settings>();
    _scenes["RoomList"] = std::make_unique<RType::Client::Scenes::RoomList>();
    _scenes["CreateRoom"] = std::make_unique<RType::Client::Scenes::CreateRoom>();
    _scenes["Room"] = std::make_unique<RType::Client::Scenes::Room>();
    _scenes["Game"] = std::make_unique<RType::Client::Scenes::Game>();

    if (_scenes[_currentScene] == nullptr)
        throw RType::Shared::Exception("Scene \"" + _currentScene + "\" not found.");
    _coordinator.init();
    _renderSystem = _coordinator.registerSystem<RType::Client::Application::AppRenderSystem>();
    instance = this;
}

RType::Client::Application::~Application()
{
}

std::string RType::Client::Application::getCurrentScene() const
{
    return _currentScene;
}

RType::Shared::ECS::Coordinator &RType::Client::Application::getCoordinator()
{
    return _scenes[_currentScene]->getCoordinator();
}

bool RType::Client::Application::isLoaded()
{
    return _scenes[_currentScene]->isLoaded();
}

bool RType::Client::Application::isLoaded(std::string scene)
{
    return _scenes[scene]->isLoaded();
}

void RType::Client::Application::changeScene(std::string scene)
{
    _tmpScene = scene;
}

void RType::Client::Application::setBootScene(std::string scene)
{
    _bootScene = scene;
}

void RType::Client::Application::setPlayerID(std::string playerID)
{
    _scenes[_currentScene]->setPlayerID(playerID);
}

::sf::RenderWindow &RType::Client::Application::getWindow()
{
    return _window;
}

void RType::Client::Application::signalHandler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    isWindowOpen = false;
    instance->signalLogic();
    exit(0);
}

void RType::Client::Application::signalLogic()
{
    _menu.sendLeaveRoom();
    _menu.sendDisconnect();
}

void RType::Client::Application::run()
{
    signal(SIGINT, this->signalHandler);
    _window.setFramerateLimit(120);
    _window.setVerticalSyncEnabled(true);
    // init global entities
    _renderSystem->load(_coordinator, _configManager);
    // load scene
    _scenes[_currentScene]->load(_deltatime, nullptr, _window, _menu, _configManager);
    while (_window.isOpen() && isWindowOpen)
    {
        _window.clear(sf::Color::Black);

        // Check if current scene exist
        if (_scenes[_currentScene] == nullptr)
            throw RType::Shared::Exception("Scene \"" + _currentScene + "\" not found.");

        auto startTime = std::chrono::high_resolution_clock::now();

        // Update scene & global renderer
        _scenes[_currentScene]->update(_deltatime, _tmpScene, _window, _lastClick, _menu, _configManager);
        _renderSystem->update(_deltatime, _coordinator, _window, _configManager, _currentScene);

        auto endTime = std::chrono::high_resolution_clock::now();
        _deltatime = std::chrono::duration_cast<std::chrono::duration<float>>(endTime - startTime).count() / 1000.f;
        if (_deltatime < 0.0167f)
            _deltatime = 0.0167f;
        else if (_deltatime > 0.1f)
            _deltatime = 0.1f;
        _deltatime *= 1000.f;

        // Changing scene
        if (_tmpScene == "bootScene")
            _tmpScene = _bootScene;
        if (_tmpScene != _currentScene)
        {
            if (_scenes[_currentScene] != nullptr)
                _scenes[_currentScene]->unload(_deltatime);
            _currentScene = _tmpScene;
            if (_scenes[_currentScene] != nullptr)
                _scenes[_currentScene]->load(_deltatime, nullptr, _window, _menu, _configManager);
        }
        _window.display();
    }
    _menu.sendDisconnect();
}

void RType::Client::Application::AppRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window, RType::Client::ConfigurationManager &configManager, std::string &currentScene)
{
    for (RType::Shared::ECS::Entity &entity : coordinator.getEntities())
    {
        try
        {
            ::std::string entityType = coordinator.getAttribute<RType::Shared::ECS::EntityType>(entity).value;
            // MUSICS ENTITIES
            if (coordinator.hasAttribute<RType::Client::ECS::Music>(entity))
            {
                RType::Client::ECS::Music &music = coordinator.getAttribute<RType::Client::ECS::Music>(entity);
                if (entityType == "menuMusic")
                {
                    _volume = 0;
                    _ss << configManager.getValue("menuMusicVolume");
                    _ss >> _volume;
                    music.volume = _volume;
                    music.hasToPlay = currentScene != "Game";
                    _ss.clear();
                }
                _musicRenderSystem.update(window, music);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void RType::Client::Application::AppRenderSystem::load(RType::Shared::ECS::Coordinator &coordinator, RType::Client::ConfigurationManager &configManager)
{
    coordinator.registerAttribute<RType::Client::ECS::Music>();
    // CREATE THE GLOBAL ENTITIES
    RType::Shared::ECS::Entity tmpEntity;

    // MUSIC OF SPLASH AND ALL MENUS / INTERFACES
    tmpEntity = coordinator.createEntity("menuMusic");
    coordinator.addAttribute<RType::Client::ECS::Music>(tmpEntity, {"Menu.ogg", std::stof(configManager.getValue("menuMusicVolume"))});
}
