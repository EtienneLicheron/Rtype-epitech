/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Room
*/

#ifndef __ROOM_HPP__
#define __ROOM_HPP__
#include "AScene.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/ServerRequestUpdateSystem.hpp"

#include "../RenderSystem/BorderRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The room scene, it will contains all the GUI before the game, like servers...
             */
            class Room : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Room object
                     *
                     */
                    Room();

                    /**
                     * @brief Destroy the Room object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the Room object
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
                     * @param lastClick the last click
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager);

                    ~Room();

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
                     * @brief The Server Request Update System
                     */
                    ServerRequestUpdateSystem _serverRequestUpdateSystem;

                    /**
                     * @brief The Room Render System
                     */
                    class RoomRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new Room Render System object
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
                    std::shared_ptr<RoomRenderSystem> _renderSystem;

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

#endif /* !__ROOM_HPP__*/
