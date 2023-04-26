/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** Game
*/

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <chrono>
#include <memory>
#include <iostream>

#include "AScene.hpp"

#include "../RenderSystem/SpriteRenderSystem.hpp"
#include "../RenderSystem/TextRenderSystem.hpp"
#include "../RenderSystem/PlayerRenderSystem.hpp"

#include "../UpdateSystem/PlayerUpdateSystem.hpp"
#include "../UpdateSystem/BackgroundUpdateSystem.hpp"
#include "../UpdateSystem/ProjectileUpdateSystem.hpp"
#include "../RenderSystem/SoundRenderSystem.hpp"
#include "../RenderSystem/MusicRenderSystem.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief Game class to create the game scene
             */
            class Game : public AScene
            {
                public:
                    /**
                     * @brief Construct a new Game object
                     */
                    Game();

                    /**
                     * @brief Destroy the Game object
                     *
                     * @param deltatime the deltatime of the game
                     * @param data the data of the game
                     * @param window the window
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void load(float deltatime, void *data, ::sf::RenderWindow &window, MenuUDP &menu, ConfigurationManager &configManager) override;

                    /**
                     * @brief Unload the Game object
                     *
                     * @param deltatime the deltatime of the game
                     */
                    void unload(float deltatime) override;

                    /**
                     * @brief Update the Game object
                     *
                     * @param deltatime the deltatime of the game
                     * @param currentScene the current scene
                     * @param window the window
                     * @param lastClick the last click
                     * @param menu the menu
                     * @param configManager the config manager
                     */
                    void update(float deltatime, std::string &currentScene, ::sf::RenderWindow &window, std::chrono::milliseconds &lastClick, MenuUDP &menu, ConfigurationManager &configManager) override;

                    ~Game() override;

                private:
                    /**
                     * @brief To register attributes in coordinator
                     */
                    void registerAttribute();

                    /**
                     * @brief The Player Update System
                     */
                    PlayerUpdateSystem _playerUpdateSystem;

                    /**
                     * @brief The Projectile Update System
                     */
                    ProjectileUpdateSystem _projectileUpdateSystem;

                    /**
                     * @brief The Background Update System
                     */
                    BackgroundUpdateSystem _backgroundUpdateSystem;

                    /**
                     * @brief The Game Render System
                     */
                    class GameRenderSystem : public RType::Shared::ECS::System
                    {
                        public:
                            /**
                             * @brief Construct a new Game Render System object
                             *
                             * @param window the window
                             */
                            void update(float deltatime, RType::Shared::ECS::Coordinator &coordinator, ::sf::RenderWindow &window);

                        private:
                            /**
                             * @brief The Sprite Render System
                             */
                            SpriteRenderSystem _spriteRenderSystem;

                            /**
                             * @brief The player Render System
                             */
                            PlayerRenderSystem _playerRenderSystem;

                            /**
                             * @brief The music render system
                             */
                            MusicRenderSystem _musicRenderSystem;

                            /**
                             * @brief The sound render system
                             */
                            SoundRenderSystem _soundRenderSystem;
                    };
                    std::shared_ptr<GameRenderSystem> _renderSystem;

                    /**
                     * @brief The event variable
                     */
                    ::sf::Event _event;
            };
        }
    }
}

#endif /* !__GAME_HPP__ */
