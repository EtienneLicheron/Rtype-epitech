/*
** EPITECH PROJECT, 2022
** RType
** File description:
** IScene
*/

#ifndef __ASCENE_HPP__
#define __ASCENE_HPP__
#define SECTION_HEADER_HEIGHT 160
#define HOVER_TRANSITION 2
#include <SFML/Graphics.hpp>
#include "../Server/MenuUDP.hpp"
#include "../Graphics/Text.hpp"
#include "../Graphics/Font.hpp"
#include "../Graphics/Sprite.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/RectangleShape.hpp"
#include "../Graphics/CircleShape.hpp"
#include "../ConfigurationManager.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief This class is the abstract base class for all the scenes
             */
            class AScene
            {
                public:
                    virtual ~AScene() = default;

                    /**
                     * @brief In a scene, call this function to start it (initialize entities, etc...)
                     *
                     * @param deltatime Time since last frame - can be useful for animations
                     * @param data Custom data (depending the scene, the needs are differents, that's why it's a ptr)
                     * @param window The window of the application, not for drawing but the data inside can be useful
                     */
                    virtual void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager) = 0;

                    /**
                     * @brief In a scene, call this function to end it (destroy entities, etc...)
                     *
                     * @param deltatime Time since last frame - can be useful for animations
                     */
                    virtual void unload(float deltatime) = 0;

                    /**
                     * @brief In a scene, call this function each frames, this function MUST handle SFML events and load the next scene if needed
                     *
                     * @param deltatime Time since last frame - can be useful for animations
                     * @param currentScene A reference to the current scene, so a scene can switch to another one
                     * @param window A reference to the sfml window, so a scene can draw on it and act on it
                     */
                    virtual void update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager) = 0;

                    /**
                     * @brief Get the Coordinator object
                     *
                     * @return Shared::ECS::Coordinator&
                     */
                    Shared::ECS::Coordinator &getCoordinator() { return _coordinator; }

                    /**
                     * @brief Get the Window object
                     *
                     * @return sf::RenderWindow&
                     */
                    bool isLoaded() const { return _loaded; }

                    /**
                     * @brief Get the Window object
                     *
                     * @return sf::RenderWindow&
                     */
                    void setPlayerID(std::string playerID) { _playerID = playerID; }

                    /**
                     * @brief Get the Player I D object
                     *
                     * @return std::string
                     */
                    std::string getPlayerID() const { return _playerID; }

                protected:
                    /**
                     * @brief The coordinator of the scene, so each scenes can have their own entities
                     */
                    Shared::ECS::Coordinator _coordinator;

                    bool _loaded = false;

                    std::string _playerID;
            };
        }
    }
}

#endif /* !__ASCENE_HPP__ */
