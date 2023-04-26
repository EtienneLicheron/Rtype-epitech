/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** HowToPlay
*/

#ifndef __HOWTOPLAY_HPP__
#define __HOWTOPLAY_HPP__
#include "AScene.hpp"
#include "../Resources.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/SwitchSceneUpdateSystem.hpp"

#include "../RenderSystem/BorderRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"
#include "../RenderSystem/KeyboardKeyRenderSystem.hpp"
#include "../AttributeClient.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The HowToPlay scene, it will contains an explanation of the game
             */
            class HowToPlay : public AScene
            {
                public:
                    /**
                     * @brief Construct a new How To Play object
                     */
                    HowToPlay();

                    /**
                     * @brief Destroy the How To Play object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the How To Play object
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
                     */
                    void update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager);

                    ~HowToPlay();

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
                     * @brief The scene render system
                     */
                    class HTPRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new HTP Render System object
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
                             * @brief The Keyboard Key Render System
                             */
                            KeyboardKeyRenderSystem _keyboardKeyRenderSystem;
                    };
                    /**
                     * @brief A pointer to the render system
                     */
                    std::shared_ptr<HTPRenderSystem> _renderSystem;

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

#endif /* !__HOWTOPLAY_HPP__ */
