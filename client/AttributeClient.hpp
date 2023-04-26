/*
** EPITECH PROJECT, 2022
** RType
** File description:
** AttributeClient
*/

#ifndef __ATTRIBUTECLIENT_HPP__
#define __ATTRIBUTECLIENT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <cstdint>
#include <chrono>
#include <memory>

#include "ECS/Entity.hpp"
#include "Graphics/Font.hpp"


namespace RType
{
    namespace Client
    {
        namespace ECS
        {
            /**
             * @brief A structure to define rectangle
             */
            struct RectangleShape
            {
                ::sf::RectangleShape value;
            };

            /**
             * @brief A structure to define circle
             */
            struct CircleShape
            {
                ::sf::CircleShape value;
            };

            /**
             * @brief A structure to define text
             */
            struct Text
            {
                ::sf::Text value;
                ::sf::Font font;
                inline Text& operator=(const Text& text)
                {
                    font = ::sf::Font(RType::Client::Graphics::Font("HelveticaNeueLTProBd.ttf").getFont());
                    value = ::sf::Text(text.value.getString(), font);
                    value.setCharacterSize(text.value.getCharacterSize());
                    value.setFillColor(text.value.getFillColor());
                    value.setPosition(text.value.getPosition());
                    return (*this);
                }
            };

            /**
             * @brief A structure to define sprite
             */
            struct Sprite
            {
                ::sf::Sprite value;
                ::sf::Texture texture;
            };

            /**
             * @brief A structure to define border
             */
            struct Border
            {
                float size;
                bool top, bottom, left, right;
                ::sf::Color color;
            };

            /**
             * @brief A structure to define hover
             */
            struct Hover
            {
                RectangleShape rect;
                float transition;
            };

            /**
             * @brief A structure to define input string
             */
            struct InputString
            {
                Text text;
                int maxSize;
                bool hover;
            };

            /**
             * @brief A structure to define server request when click
             */
            struct ServerRequest
            {
                std::string type;
                std::string body;
                RType::Shared::ECS::Entity link;
            };

            /**
             * @brief A structure to define login request
             */
            struct LoginRequest
            {
                RType::Shared::ECS::Entity username, address, port;
            };

            /**
             * @brief A structure to define switch scene when click
             */
            struct SwitchScene
            {
                std::string value;
            };

            /**
             * @brief A structure to define a position
             */
            struct Position {
                float x;
                float y;
            };

            struct DisplayName {
                sf::Text text;
            };

            /**
             * @brief A structure to define a color
             */
            struct Color {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t a;
            };

            /**
             * @brief A structure to define a keyboard key
             */
            struct KeyboardKey {
                char character = 'A';
                ::sf::Vector2f position = {0, 0};
                int height = 50;
                bool autoPress = false;
                bool pressed = false;
                ::sf::RectangleShape rectangle = ::sf::RectangleShape();
                ::sf::RectangleShape shadow = ::sf::RectangleShape();
                ::sf::Text text = ::sf::Text();
                ::sf::Font font = ::sf::Font();
                std::chrono::time_point<std::chrono::system_clock> clock;
            };

            /**
             * @brief A structure to define a sound.<br />
             * It is a lightweight object that plays loaded audio data from a soundBuffer. It should be used for small sounds that can fit in memory and should suffer no lag when they are played. Examples are gun shots, foot steps, etc.
             */
            struct Sound {
                /**
                 * @brief Hold the fileName of the sound file.
                 */
                std::string fileName;
                /**
                 * @brief It hold the volume of the music.
                 */
                float volume = 100.0f;
                /**
                 * @brief Define if the sound should play or not. (once it's played, it will be set to false)
                 */
                bool playing = false;
                /**
                 * @brief It holds the memory audio stream
                 */
                std::shared_ptr<::sf::Sound> value = nullptr;
                /**
                 * @brief Our buffer in memory
                 */
                std::shared_ptr<::sf::SoundBuffer> buffer = nullptr;
            };

            /**
             * @brief A structure to define a music.<br />
             * This attribute doesn't load all the audio data into memory, instead it streams it on the fly from the source file. It is typically used to play compressed music that lasts several minutes, and would otherwise take many seconds to load and eat hundreds of MB in memory.
             * Also, if a music have multiple songs (with the playlist), at the end of the music, we will re-rerandomize to go on another song.
             */
            struct Music {
                /**
                 * @brief Hold the fileName of the music file.
                 */
                std::string fileName;
                /**
                 * @brief It hold the volume of the music.
                 */
                float volume = 100.0f;
                /**
                 * @brief Define if the music should play or not.
                 */
                bool hasToPlay = true;
                /**
                 * @brief It holds the on-the-fly audio stream.
                 */
                std::shared_ptr<::sf::Music> value = nullptr;
                /**
                 * @brief If the file has also a text file in its directory, we will load differents timecodes and randomize them to hear differents song.
                 */
                std::vector<std::string> playlist = std::vector<std::string>();
                /**
                 * @brief If a playlist exists, it holds the current index in the playlist being played. Else, it holds -1. It holds -42 by default, to check if we already searched for a playlist or not.
                 */
                int currentSong = -42;
            };

            /**
             * @brief A structure to define a slider (with a bar and a cursor)
             */
            struct Slider {
                /**
                 * @brief The current value of the slider
                 */
                int value;
                /**
                 * @brief Define the height of the bar (the cursor will be automatically scaled of 20% more than the bar)
                 */
                int height;
                /**
                 * @brief Define the width of the bar (the cursor will be automatically scaled of 20% more than the bar)
                 */
                int width;
                /**
                 * @brief Define the position of the slider
                 */
                ::sf::Vector2f position;
                /**
                 * @brief The maximum value of the slider
                 */
                int maxValue = 100;
                /**
                 * @brief The minimum value of the slider
                 */
                int minValue = 0;
                /**
                 * @brief The color of the bar
                 */
                Color barColor = {0, 0, 0, 255};
                /**
                 * @brief The color of the cursor
                 */
                Color cursorColor = {150, 150, 150, 255};
                /**
                 * @brief The color of the cursor when it's hovered
                 */
                Color cursorHoverColor = {200, 200, 200, 255};
                /**
                 * @brief The color of the cursor when it's pressed
                 */
                Color cursorActiveColor = {100, 100, 100, 255};
                /**
                 * @brief The color of the popup when it's active
                 */
                Color popupColor = {28, 28, 28, 255};
                /**
                 * @brief The color of the popup text
                 */
                Color popupTextColor = {255, 255, 255, 255};
            };

            /**
             * @brief A structure to define a save btn action
             */
            struct SaveAction
            {
                RType::Shared::ECS::Entity menuMusicVolumeEntity, gameMusicVolumeEntity, gameSoundsVolumeEntity;
            };
            /**
             * @brief A structure to define an image
             */
            struct Image {
                /**
                 * @brief The filename
                 */
                ::std::string fileName;
                /**
                 * @brief The scale of the image
                 */
                ::sf::Vector2f scale = {1, 1};
                /**
                 * @brief The sprite
                 */
                ::sf::Sprite sprite = ::sf::Sprite();
                /**
                 * @brief The texture
                 */
                ::sf::Texture texture = ::sf::Texture();
                /**
                 * @brief Is the image loaded ?
                 */
                bool loaded = false;
            };
        }
    }
}

#endif /* !__ATTRIBUTECLIENT_HPP__ */
