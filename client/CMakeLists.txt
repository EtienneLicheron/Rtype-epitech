add_executable(client
    Graphics/CircleShape.cpp
    Graphics/CircleShape.hpp
    Graphics/Font.cpp
    Graphics/Font.hpp
    Graphics/RectangleShape.cpp
    Graphics/RectangleShape.hpp
    Graphics/Sprite.cpp
    Graphics/Sprite.hpp
    Graphics/Text.cpp
    Graphics/Text.hpp
    Graphics/Texture.cpp
    Graphics/Texture.hpp

    Scenes/AScene.hpp
    Scenes/Game.hpp
    Scenes/Game.cpp
    Scenes/HowToPlay.hpp
    Scenes/HowToPlay.cpp
    Scenes/Login.hpp
    Scenes/Login.cpp
    Scenes/Menu.cpp
    Scenes/Menu.hpp
    Scenes/Room.cpp
    Scenes/Room.hpp
    Scenes/CreateRoom.hpp
    Scenes/CreateRoom.cpp
    Scenes/RoomList.hpp
    Scenes/RoomList.cpp
    Scenes/Settings.hpp
    Scenes/Settings.cpp
    Scenes/Splash.cpp
    Scenes/Splash.hpp

    RenderSystem/BorderRenderSystem.cpp
    RenderSystem/BorderRenderSystem.hpp
    RenderSystem/KeyboardKeyRenderSystem.cpp
    RenderSystem/KeyboardKeyRenderSystem.hpp
    RenderSystem/MusicRenderSystem.cpp
    RenderSystem/MusicRenderSystem.hpp
    RenderSystem/PlayerRenderSystem.cpp
    RenderSystem/PlayerRenderSystem.hpp
    RenderSystem/SliderRenderSystem.cpp
    RenderSystem/SliderRenderSystem.hpp
    RenderSystem/SoundRenderSystem.cpp
    RenderSystem/SoundRenderSystem.hpp
    RenderSystem/SpriteRenderSystem.hpp
    RenderSystem/SpriteRenderSystem.cpp
    RenderSystem/TextRenderSystem.hpp
    RenderSystem/TextRenderSystem.cpp

    UpdateSystem/BackgroundUpdateSystem.hpp
    UpdateSystem/BackgroundUpdateSystem.cpp
    UpdateSystem/HoverUpdateSystem.hpp
    UpdateSystem/HoverUpdateSystem.cpp
    UpdateSystem/InputStringUpdateSystem.hpp
    UpdateSystem/InputStringUpdateSystem.cpp
    UpdateSystem/LoginRequestUpdateSystem.hpp
    UpdateSystem/LoginRequestUpdateSystem.cpp
    UpdateSystem/PlayerUpdateSystem.hpp
    UpdateSystem/PlayerUpdateSystem.cpp
    UpdateSystem/ProjectileUpdateSystem.hpp
    UpdateSystem/ProjectileUpdateSystem.cpp
    UpdateSystem/SaveActionUpdateSystem.hpp
    UpdateSystem/SaveActionUpdateSystem.cpp
    UpdateSystem/ServerRequestUpdateSystem.hpp
    UpdateSystem/ServerRequestUpdateSystem.cpp
    UpdateSystem/SwitchSceneUpdateSystem.hpp
    UpdateSystem/SwitchSceneUpdateSystem.cpp

    Application.cpp
    Application.hpp
    AttributeClient.hpp
    ConfigurationManager.cpp
    ConfigurationManager.hpp
    Resources.cpp
    Resources.hpp
    main.cpp

    Server/MenuUDP.cpp
    Server/MenuUDP.hpp
    Server/MenuHandleReceived.cpp
    Server/GameHandleReceived.cpp
    Server/SendFunctions.cpp
    Server/GameUDP.hpp
    Server/GameUDP.cpp
)
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(client PROPERTIES CXX_STANDARD 17)

# DEBUG
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

# RESOURCES
FILE(COPY "Resources/Fonts/HelveticaNeueLTProBd.ttf" DESTINATION "Resources/Fonts")
FILE(COPY "Resources/Musics/Game.ogg" DESTINATION "Resources/Musics")
FILE(COPY "Resources/Musics/Game.txt" DESTINATION "Resources/Musics")
FILE(COPY "Resources/Musics/Menu.ogg" DESTINATION "Resources/Musics")
FILE(COPY "Resources/Musics/Menu.txt" DESTINATION "Resources/Musics")
FILE(COPY "Resources/Sounds/Laser.wav" DESTINATION "Resources/Sounds")
FILE(COPY "Resources/Sounds/Explosion.wav" DESTINATION "Resources/Sounds")
FILE(COPY "Resources/Sprites/player_1.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/player_2.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/player_3.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/player_4.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/laser1.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/laser2.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/background.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/enemy_1.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/enemy_2.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Sprites/enemy_3.png" DESTINATION "Resources/Sprites")
FILE(COPY "Resources/Images/logo.png" DESTINATION "Resources/Images")

include_directories(${CMAKE_SOURCE_DIR}/shared)

set(math_lib "m")
if (WIN32)
    set(math_lib "msvcrt")
endif()

target_link_libraries(client PRIVATE
    shared
    asio::asio
    sfml-graphics
    sfml-network
    sfml-audio
    ${math_lib}
)

install(TARGETS client RUNTIME DESTINATION .)
