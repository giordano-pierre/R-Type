project(r-type_server VERSION 1.0 LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(Sol2 CONFIG REQUIRED)

set(SRC
    src/server_main.cpp
    src/LevelLoader.cpp
    src/tools.cpp
    src/Child.cpp
    src/systems/parent/UDPServer.cpp
    src/systems/parent/MainMessageHandlerSys.cpp
    src/systems/parent/ResendEventSys.cpp
    src/systems/parent/CheckWinSys.cpp
    src/systems/parent/LifeSys.cpp
    src/systems/parent/TriggerChildSys.cpp
    src/systems/parent/UpdateSys.cpp
    src/systems/child/CollisionSystem.cpp
    src/systems/child/HealthSystem.cpp
    src/systems/child/RemoveSys.cpp
    src/systems/child/MovementSystem.cpp
    src/systems/child/SubMessageHandlerSys.cpp
    src/systems/child/EnemiesSystem.cpp
)

add_executable(r-type_server ${SRC})

target_include_directories(r-type_server
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/installed/x64-linux/include
        ${LUA_INCLUDE_DIR}
)

target_link_libraries(r-type_server
    PUBLIC
        ECS
        Shared
    PRIVATE
        nlohmann_json::nlohmann_json
        ${LUA_LIBRARIES}
        sol2
)
