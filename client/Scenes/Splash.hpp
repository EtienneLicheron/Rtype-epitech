/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Splash
*/

#ifndef __SPLASH_HPP__
#define __SPLASH_HPP__
#define SPLASH_DURATION_IN_SECS 3
#define SPLASH_TRANSITION_SPEED 1
#define OPACITY_SPEED 7000
#include <random>
#include "AScene.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The splash screen scene, it will contain a white bg, the epitech logo, and a bunch of different circles of different colors. Some will be black so at the end, it will grow and make the screen black.
             */
            class Splash : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Splash object
                     */
                    Splash();

                    /**
                     * @brief Destroy the Splash object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the Splash object
                     *
                     * @param deltatime
                     */
                    void unload(float deltatime);

                    /**
                     * @brief Update the scene
                     *
                     * @param deltatime the deltatime
                     * @param currentScene the current scene
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager);

                    ~Splash();

                private:
                    /**
                     * @brief To register attributes in coordinator
                     */
                    void registerAttributes();

                    /**
                     * @brief The Splash Render System
                     */
                    class SplashRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new Splash Render System object
                             *
                             * @param deltatime the deltatime
                             * @param coordinator the coordinator
                             * @param window the window
                             */
                            void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window);
                    };
                    std::shared_ptr<SplashRenderSystem> _renderSystem;

                    /**
                     * @brief The start time of the scene
                     */
                    std::chrono::time_point<std::chrono::system_clock> _startTime;

                    /**
                     * @brief The logo variable
                     */
                    RType::Shared::ECS::Entity _logo;

                    /**
                     * @brief The transition circle entity
                     */
                    RType::Shared::ECS::Entity _transitionCircle;

                    /**
                     * @brief The event variable
                     */
                    ::sf::Event _event;
            };
        }
    }
}

#endif /* !__SPLASH_HPP__ */
