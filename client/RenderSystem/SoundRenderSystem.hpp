/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SoundRenderSystem
*/

#ifndef __SOUNDRENDERSYSTEM_HPP__
    #define __SOUNDRENDERSYSTEM_HPP__
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include "../AttributeClient.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The SoundRenderSystem class
             */
            class SoundRenderSystem
            {
                public:
                    /**
                     * @brief Construct a new Sound Render System object
                     *
                     * @param window the window
                     * @param sound the sound
                     */
                    void update(::sf::RenderWindow &window, RType::Client::ECS::Sound &sound);

                private:
                    /**
                     * @brief The temporary sound to render
                     *
                     * @param sound the sound
                     */
                    void initSound(RType::Client::ECS::Sound &sound);
            };
        }
    }
}

#endif /* !__SOUNDRENDERSYSTEM_HPP__ */
