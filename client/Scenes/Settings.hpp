/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Settings
*/

#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__
#include "AScene.hpp"
#include "../Resources.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/SwitchSceneUpdateSystem.hpp"
#include "../UpdateSystem/SaveActionUpdateSystem.hpp"

#include "../RenderSystem/BorderRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"
    #include "../RenderSystem/SliderRenderSystem.hpp"
#include "../AttributeClient.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {

            /**
             * @brief The settings scene, it will allow the user to configure its game, using the ConfigurationManager
             */
            class Settings : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Settings object
                     */
                    Settings();

                    /**
                     * @brief Destroy the Settings object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the Settings object
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

                    ~Settings();

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
                     * @brief The Save Action Update System
                     */
                    SaveActionUpdateSystem _saveActionUpdateSystem;

                    /**
                     * @brief The scene render system
                     */
                    class SettingsRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new Settings Render System object
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

                            /**
                             * @brief The Slider Render System
                             */
                            SliderRenderSystem _sliderRenderSystem;
                    };
                    /**
                     * @brief A pointer to the render system
                     */
                    std::shared_ptr<SettingsRenderSystem> _renderSystem;

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

#endif /* !__SETTINGS_HPP__ */
