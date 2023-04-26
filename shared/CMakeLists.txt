add_library(shared

    ECS/Attribute.hpp
    ECS/AttributeArray.hpp
    ECS/AttributeManager.hpp
    ECS/Coordinator.cpp
    ECS/Coordinator.hpp
    ECS/Entity.hpp
    ECS/EntityManager.cpp
    ECS/EntityManager.hpp
    ECS/IAttributeArray.hpp
    ECS/Signature.hpp
    ECS/System.hpp
    ECS/SystemManager.hpp

    Exception.cpp
    Exception.hpp
    Packet.hpp
    Packet.cpp
    Utils.cpp
    Utils.hpp
    UUID.cpp
    UUID.hpp
    LockedQueue.hpp
    Bestiaire.cpp
    Bestiaire.hpp
)
set_target_properties(shared PROPERTIES CXX_STANDARD 17)

set(math_lib "m")
if(WIN32)
    set(math_lib "msvcrt")
endif()

target_link_libraries(shared PRIVATE
    asio::asio
    ${math_lib}
    sfml-graphics
    sfml-network
)

install(TARGETS shared
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
