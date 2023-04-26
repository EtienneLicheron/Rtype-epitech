/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicRenderSystem
*/

#ifndef __MUSICRENDERSYSTEM_HPP__
    #define __MUSICRENDERSYSTEM_HPP__
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <string>
    #include <vector>
    #include <fstream>
    #include <sstream>
    #include <random>
    #include "../AttributeClient.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The Music Render System class
             */
            class MusicRenderSystem
            {
                public:
                    /**
                     * @brief The function to call in the scene that want a music or a playlist.
                     *
                     * @param window The window where to render the music
                     * @param music The music to render
                     */
                    void update(::sf::RenderWindow &window, RType::Client::ECS::Music &music);

                private:
                    /**
                     * @brief When loading a music, this will check if it has a playlist and load it.
                     *
                     * @param music The music to check
                     * @return true If a playlist is found
                     * @return false If a playlist isn't found
                     */
                    bool initPlaylist(RType::Client::ECS::Music &music);

                    /**
                     * @brief An util function to update an music inside a playlist.
                     */
                    void updatePlaylist(RType::Client::ECS::Music &music);
            };

        }
    }
}

#endif /* !__MUSICRENDERSYSTEM_HPP__ */
