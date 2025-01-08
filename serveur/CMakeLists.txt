project(r-type_server VERSION 1.0 LANGUAGES CXX)

set(SRC
    src/server_main.cpp
    src/tools.cpp
    src/UDPServer.cpp
    src/systems/parent/MainMessageHandlerSys.cpp
    src/systems/child/LifeSys.cpp
    # src/ServerHandlerSystem.cpp
    # src/GameLogicSystem.cpp
    # src/CollisionSystem.cpp
    # src/HealthSystem.cpp
    # src/MovementSystem.cpp
)

add_executable(r-type_server ${SRC})

target_include_directories(r-type_server
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(r-type_server
    PUBLIC
        ECS
        Shared
)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(r-type_server PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(r-type_server
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/installed/x64-linux/include
)
