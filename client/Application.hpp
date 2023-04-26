/*
** EPITECH PROJECT, 2022
** RType
** File description:
** Application
*/

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
#include <asio.hpp>
#include <iostream>
#include <memory>
#include <map>
#include <chrono>
#include <array>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <iomanip>
#include <optional>

#include "Server/MenuUDP.hpp"
#include "ConfigurationManager.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "Packet.hpp"

#include "Scenes/Splash.hpp"
#include "Scenes/Login.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/HowToPlay.hpp"
#include "Scenes/Settings.hpp"
#include "Scenes/Room.hpp"
#include "Scenes/RoomList.hpp"
#include "Scenes/CreateRoom.hpp"
#include "Scenes/Game.hpp"

#include "RenderSystem/MusicRenderSystem.hpp"

static bool isWindowOpen = true;

namespace RType
{
    namespace Client
    {
        /**
         * @brief This class is the main class of the client, it will handle all the logic of the program
         * @details It will handle the scenes, the network, the rendering, etc...
         */
        class Application
        {
        public:
            /**
             * @brief constructor of the Application class
             * @param host the host of the server
             * @param port the port of the server
             * @param username the name of the client
             */
            Application(std::string host, unsigned short port, ::std::string username);
            ~Application();

            /**
             * @brief Get the current scene
             */
            ::std::string getCurrentScene() const;

            /**
             * @brief Get Coordinator
             * @return the coordinator of the current scene
             */
            RType::Shared::ECS::Coordinator &getCoordinator();

            /**
             * @brief Check is the scene is loaded
             * @return true if the scene is loaded, false otherwise
             */
            bool isLoaded();

            /**
             * @brief Check is the scene is loaded
             * @param scene the scebe to check if is loaded
             * @return true if the scene is loaded, false otherwise
             */
            bool isLoaded(std::string scene);

            /**
             * @brief Change the current scene
             */
            void changeScene(::std::string scene);

            /**
             * @brief Set the boot scene
             */
            void setBootScene(::std::string scene);

            /**
             * @brief Set player ID in scene boot scene
             */
            void setPlayerID(::std::string playerID);

            /**
             * @brief Get window
             */
            ::sf::RenderWindow &getWindow();

            /**
             * @brief This function will start the application
             */
            void run();

            /**
             * @brief This function will handle the signals
             * @param signum
             */
            static void signalHandler(int signum);
            /**
             * @brief This function will handle packages to send when a signal is received
             */
            void signalLogic();

        private:
            /**
             * @brief Instance of the Application class
            */
            static Application *instance;
            /**
             * @brief Time between two frames (in seconds)
             */
            float _deltatime;

            /**
             * @brief The current window
             */
            ::sf::RenderWindow _window;

            /**
             * @brief The boot scene
             */
            ::std::string _bootScene;

            /**
             * @brief A temporary string used to load / unload between two scenes
             */
            ::std::string _tmpScene;

            /**
             * @brief The current scene
             */
            ::std::string _currentScene;

            /**
             * @brief The scenes of the application (key = scene name, value = scene ptr)
             */
            ::std::map<::std::string, ::std::unique_ptr<Scenes::AScene>> _scenes;

            /**
             * @brief The menu client UDP
             */
            RType::Client::MenuUDP _menu;

            /**
             * @brief Configuration Manager, to manage local data
             */
            ConfigurationManager _configManager;

            /**
             * @brief Time of last click
             */
            ::std::chrono::milliseconds _lastClick;

            /**
             * @brief The coordinator of the current scene
             */
            RType::Shared::ECS::Coordinator _coordinator;

            /**
             * @brief The global application render system
             */
            class AppRenderSystem : public RType::Shared::ECS::System
            {
            public:
                void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window, RType::Client::ConfigurationManager &configManager, std::string &currentScene);
                void load(RType::Shared::ECS::Coordinator &coordinator, RType::Client::ConfigurationManager &configManager);

            private:
                /**
                 * @brief The Music Render System
                 */
                Scenes::MusicRenderSystem _musicRenderSystem;
                /**
                 * @brief Stringstream for the parsing of the volume in the menu
                 */
                std::stringstream _ss;
                /**
                 * @brief Volume in the menu;
                 */
                int _volume;
            };
            ::std::shared_ptr<AppRenderSystem> _renderSystem;
        };
    }
}

#endif /* !__APPLICATION_HPP__ */
