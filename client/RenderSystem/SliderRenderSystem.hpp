/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** SliderRenderSystem
*/

#ifndef __SLIDERRENDERSYSTEM_HPP__
    #define __SLIDERRENDERSYSTEM_HPP__
    #include <SFML/Graphics.hpp>
    #include "../AttributeClient.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The SliderRenderSystem class
             */
            class SliderRenderSystem
            {
                public:
                    /**
                     * @brief Construct a new Slider Render System object
                     *
                     * @param window the window
                     * @param slider the slider
                     */
                    void update(::sf::RenderWindow &window, RType::Client::ECS::Slider &slider);

                private:
                    ::sf::RectangleShape _tmpBar;
                    ::sf::RectangleShape _tmpCursor;
            };

        }
    }
}

#endif // __SLIDERRENDERSYSTEM_HPP__
