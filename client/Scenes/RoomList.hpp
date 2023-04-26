/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** RoomList
*/

#ifndef __ROOMLIST_HPP__
#define __ROOMLIST_HPP__
#include "AScene.hpp"

#include "../UpdateSystem/HoverUpdateSystem.hpp"
#include "../UpdateSystem/SwitchSceneUpdateSystem.hpp"
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
             * @brief The RoomList scene, it will contain access to the rooms.
             */
            class RoomList : public AScene
            {
                public:
                    /**
                     * @brief Construct a new RoomList object
                     */
                    RoomList();

                    /**
                     * @brief Destroy the RoomList object
                     *
                     * @param deltatime the deltatime
                     * @param data the data
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager);

                    /**
                     * @brief Unload the RoomList object
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

                    ~RoomList();

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
                     * @brief The Server Request Update System
                     */
                    ServerRequestUpdateSystem _serverRequestUpdateSystem;

                    /**
                     * @brief The RoomList Render System
                     */
                    class RoomListRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new RoomList Render System object
                             *
                             * @param deltatime the deltatime
                             * @param coordinator the coordinator
                             * @param window the window
                             * @param menu the menu
                             */
                            void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window, MenuUDP &menu);

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
                    std::shared_ptr<RoomListRenderSystem> _renderSystem;

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

#endif /* !__ROOMLIST_HPP__ */
