cmake_minimum_required(VERSION 3.16)

project(r-type_client VERSION 1.0 LANGUAGES CXX)

set(SRC
    src/client_main.cpp
    src/TextureManager.cpp
    src/components/Drawable.cpp
    src/components/Position.cpp
    src/components/Velocity.cpp
    src/components/Playable.cpp
    src/components/Tag.cpp
    src/components/Window.cpp
    src/components/Hitbox.cpp
    src/components/Text.cpp
    src/components/Selectable.cpp
    src/events/FrameEvent.cpp
    src/events/TicEvent.cpp
    src/systems/AnimeSys.cpp
    src/systems/BorderSys.cpp
    src/systems/CheatSys.cpp
    src/systems/LifeSys.cpp
    src/systems/MessageHandlerSys.cpp
    src/systems/MoveSys.cpp
    src/systems/PauseSys.cpp
    src/systems/PressButtonSys.cpp
    src/systems/SelectSys.cpp
    src/systems/ShootSys.cpp
    src/systems/UDPClient.cpp
    src/systems/WindowSys.cpp
    src/buttonFunctions.cpp
    src/createEntities.cpp
    src/loadSystems.cpp
    src/clientTools.cpp
)

add_executable(r-type_client ${SRC})

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(r-type_client PRIVATE ECS sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

target_link_libraries(r-type_client
    PUBLIC
        ECS Shared
)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
