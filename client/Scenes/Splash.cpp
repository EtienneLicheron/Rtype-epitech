/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Splash
*/

#include "Splash.hpp"

RType::Client::Scenes::Splash::Splash() : _startTime(std::chrono::system_clock::now())
{
}

RType::Client::Scenes::Splash::~Splash()
{
}

void RType::Client::Scenes::Splash::load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager)
{
    std::default_random_engine generator(std::random_device{}());
    std::uniform_real_distribution<float> randPositionX(0.0f, window.getSize().x);
    std::uniform_real_distribution<float> randPositionY(0.0f, window.getSize().y);
    std::uniform_real_distribution<float> randRadius(2.0f, 6.0f);

    // Init coordinator
    _coordinator.init();

    // Register attributes
    _coordinator.registerAttribute<RType::Client::ECS::CircleShape>();
    _coordinator.registerAttribute<RType::Client::ECS::Image>();
    _coordinator.registerAttribute<RType::Client::ECS::Position>();

    // Register the system
    _renderSystem = _coordinator.registerSystem<SplashRenderSystem>();

    // Circles
    for (int i = 0; i < MAX_ENTITIES - 2; i++)
        _coordinator.addAttribute<RType::Client::ECS::CircleShape>(_coordinator.createEntity("circle"), {RType::Client::Graphics::CircleShape({randPositionX(generator), randPositionY(generator)}, randRadius(generator), {1.f, 1.f}, {255, 255, 255, 255}).getCircleShape()});

    // Logo
    _logo = _coordinator.createEntity("logo");
    _coordinator.addAttribute<RType::Client::ECS::Image>(_logo, {"logo.png", {0.25f, 0.25f}});
    _coordinator.addAttribute<RType::Client::ECS::Position>(_logo, {static_cast<float>(window.getSize().x / 2 - 200), static_cast<float>(window.getSize().y / 2 - 200)});

    // Circle of transition
    _transitionCircle = _coordinator.createEntity("transition");
    _coordinator.addAttribute<RType::Client::ECS::CircleShape>(_transitionCircle, {RType::Client::Graphics::CircleShape({static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)}, 0, {1.f, 1.f}, {0, 0, 0, 0}).getCircleShape()});

    // Set the current load state
    _loaded = true;
}

void RType::Client::Scenes::Splash::unload(float deltatime)
{
    (void)deltatime;

    for (auto &entity : _coordinator.getEntities())
        _coordinator.destroyEntity(entity);
}

void RType::Client::Scenes::Splash::update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager)
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
    }

    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count() >= SPLASH_DURATION_IN_SECS)
    {
        if (_coordinator.hasAttribute<RType::Client::ECS::CircleShape>(_transitionCircle)) {
            auto &circle = _coordinator.getAttribute<RType::Client::ECS::CircleShape>(_transitionCircle);
            circle.value.setRadius(circle.value.getRadius() + SPLASH_TRANSITION_SPEED * deltatime);
            if (circle.value.getFillColor().a + (OPACITY_SPEED * deltatime) >= 255)
                circle.value.setFillColor({circle.value.getFillColor().r, circle.value.getFillColor().g, circle.value.getFillColor().b, 255});
            else
                circle.value.setFillColor({circle.value.getFillColor().r, circle.value.getFillColor().g, circle.value.getFillColor().b, static_cast<sf::Uint8>(circle.value.getFillColor().a + OPACITY_SPEED * deltatime)});
            circle.value.setPosition({window.getSize().x / 2 - circle.value.getRadius(), window.getSize().y / 2 - circle.value.getRadius()});
            if (circle.value.getRadius() > window.getSize().x)
            {
                currentScene = "bootScene";
                return;
            }
        }
    }
    else
    {
        for (auto &entity : _coordinator.getEntities())
        {
            if (_coordinator.hasAttribute<RType::Client::ECS::CircleShape>(entity)) {
                auto &circle = _coordinator.getAttribute<RType::Client::ECS::CircleShape>(entity);
                circle.value.setPosition({circle.value.getPosition().x + (100 * deltatime * std::cos(circle.value.getPosition().y / 1000)) / 20, circle.value.getPosition().y + (100 * deltatime * std::sin(circle.value.getPosition().x / 1000)) / 20});
            } else {
                auto &image = _coordinator.getAttribute<RType::Client::ECS::Image>(entity);
                auto &position = _coordinator.getAttribute<RType::Client::ECS::Position>(entity);
                if (!image.loaded) {
                    image.texture.loadFromFile(RType::Client::Resources::getPath(Resources::Image, image.fileName));
                    image.sprite.setTexture(image.texture);
                    image.sprite.setScale(image.scale);
                    position.x = window.getSize().x / 2 - image.sprite.getGlobalBounds().width / 2;
                    position.y = window.getSize().y / 2 - image.sprite.getGlobalBounds().height / 2;
                    image.sprite.setPosition(position.x, position.y);
                    image.loaded = true;
                }
            }
        }
    }

    _renderSystem.get()->update(deltatime, _coordinator, window);
}

void RType::Client::Scenes::Splash::SplashRenderSystem::update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, sf::RenderWindow &window)
{
    static std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

    for (auto &entity : coordinator.getEntities())
    {
        try
        {
            if (coordinator.hasAttribute<RType::Client::ECS::CircleShape>(entity)) {
                auto &circle = coordinator.getAttribute<RType::Client::ECS::CircleShape>(entity);
                window.draw(circle.value);
            } else {
                auto &image = coordinator.getAttribute<RType::Client::ECS::Image>(entity);
                window.draw(image.sprite);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
