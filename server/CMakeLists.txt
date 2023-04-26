add_executable(server
    AttributeServer.hpp
    Game.cpp
    Game.hpp
    GameHandleReceived.cpp
    HandleReceived.cpp
    main.cpp
    Room.cpp
    Room.hpp
    ServerUDP.cpp
    ServerUDP.hpp
    Users.cpp
    Users.hpp
    Enemies.cpp
)
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(server PROPERTIES CXX_STANDARD 17)

# DEBUG
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

include_directories(${CMAKE_SOURCE_DIR}/shared)

set(math_lib "m")
if (WIN32)
    set(math_lib "msvcrt")
endif()

target_link_libraries(server PRIVATE
    shared
    asio::asio
    ${math_lib}
)

install(TARGETS server RUNTIME DESTINATION .)
