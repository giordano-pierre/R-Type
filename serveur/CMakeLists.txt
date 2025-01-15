project(r-type_server VERSION 1.0 LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(Sol2 CONFIG REQUIRED)

set(SRC
    src/server_main.cpp
    src/ServerHandlerSystem.cpp
    src/UDPServer.cpp
    src/GameLogicSystem.cpp
    src/CollisionSystem.cpp
    src/HealthSystem.cpp
    src/MovementSystem.cpp
    src/EnemiesSystem.cpp
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
        Systems
    PRIVATE
        nlohmann_json::nlohmann_json
        ${LUA_LIBRARIES}
        sol2
)