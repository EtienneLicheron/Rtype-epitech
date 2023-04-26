/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** KeyboardKeyRenderSystem
*/

#ifndef __KEYBOARDKEYRENDERSYSTEM_HPP__
    #define __KEYBOARDKEYRENDERSYSTEM_HPP__
    #include "../AttributeClient.hpp"
    #include "../RenderSystem/KeyboardKeyRenderSystem.hpp"
    #include "../Resources.hpp"

namespace RType
{
    namespace Client
    {
        namespace Scenes
        {
            /**
             * @brief The KeyboardKeyRenderSystem class
             */
            class KeyboardKeyRenderSystem
            {
                public:
                    /**
                     * @brief Construct a new Keyboard Key Render System object
                     *
                     * @param deltatime the deltatime
                     * @param window the window
                     * @param key the key
                     */
                    void update(float deltatime, ::sf::RenderWindow &window, RType::Client::ECS::KeyboardKey &key);

                private:
                    /**
                     * @brief The temporary keyboard key to render
                     *
                     * @param key
                     */
                    void init(RType::Client::ECS::KeyboardKey &key);
            };
        }
    }
}

#endif /* !__KEYBOARDKEYRENDERSYSTEM_HPP__ */
