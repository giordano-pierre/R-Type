cmake_minimum_required(VERSION 3.16)

project(r-type_client VERSION 1.0 LANGUAGES CXX)

set(SRC
    src/client_main.cpp
    src/TextureManager.cpp
    src/components/Drawable.cpp
    src/components/Position.cpp
    src/components/Velocity.cpp
    src/components/Playable.cpp
    src/components/Type.cpp
    src/components/Window.cpp
    src/components/Hitbox.cpp
    src/events/FrameEvent.cpp
    src/events/TicEvent.cpp
    src/systems/FrameSys.cpp
    src/systems/MoveSys.cpp
    src/systems/WindowSys.cpp
    src/systems/PauseSys.cpp
    src/systems/BorderSys.cpp
    src/systems/ShootSys.cpp
    src/systems/CheatSys.cpp
    src/systems/SelectSys.cpp
    src/tools.cpp
)

add_executable(r-type_client ${SRC})

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(r-type_client PRIVATE ECS sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
