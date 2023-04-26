/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Login
*/

#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__
#include "AScene.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/InputStringUpdateSystem.hpp"
#include "../UpdateSystem/LoginRequestUpdateSystem.hpp"

#include "../RenderSystem/BorderRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The login scene, it will contains all the GUI before the game, like servers...
             */
            class Login : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Login object
                     *
                     */
                    Login();

                    /**
                     * @brief Destroy the Login object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the Login object
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

                    ~Login();

                private:
                    /**
                     * @brief To register attributes in coordinator
                     */
                    void registerAttributes();

                    /**
                     * @brief The Hover Update System
                     */
                    HoverUpdateSystem _hoverUpdateSystem;

                    /**
                     * @brief The Input String Update System
                     */
                    InputStringUpdateSystem _inputStringUpdateSystem;

                    /**
                     * @brief The Login Request Update System
                     */
                    LoginRequestUpdateSystem _loginRequestUpdateSystem;

                    /**
                     * @brief The Login Render System
                     */
                    class LoginRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new Login Render System object
                             *
                             * @param deltatime the deltatime
                             * @param coordinator the coordinator
                             * @param window the window
                             */
                            void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window);

                        private:
                            /**
                             * @brief The Border Render System
                             */
                            BorderRenderSystem _borderRenderSystem;

                            /**
                             * @brief The Text Render System
                             */
                            TextRenderSystem _textRenderSystem;
                    };
                    std::shared_ptr<LoginRenderSystem> _renderSystem;

                    /**
                     * @brief The transition circle entity
                     */
                    RType::Shared::ECS::Entity _transitionCircle;

                    /**
                     * @brief The mouse position
                     */
                    sf::Vector2i _mouse = {0, 0};

                    /**
                     * @brief The event variable
                     */
                    ::sf::Event _event;
            };
        }
    }
}

#endif /* !__LOGIN_HPP__ */
