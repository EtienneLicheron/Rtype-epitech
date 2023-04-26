/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Menu
*/

#ifndef __MENU_HPP__
#define __MENU_HPP__
#include "AScene.hpp"
#include "../Resources.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/SwitchSceneUpdateSystem.hpp"

#include "../RenderSystem/BorderRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The menu scene, it will contains all the GUI before the game, like servers, rooms, parameters, profiles...
             */
            class Menu : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Menu object
                     */
                    Menu();

                    /**
                     * @brief Destroy the Menu object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the Menu object
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

                    ~Menu();

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
                     * @brief The Switch Scene Update System
                     */
                    SwitchSceneUpdateSystem _switchSceneUpdateSystem;

                    /**
                     * @brief The Menu Render System
                     */
                    class MenuRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
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
                    std::shared_ptr<MenuRenderSystem> _renderSystem;

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

#endif /* !__MENU_HPP__ */
