project(r-type_server VERSION 1.0 LANGUAGES CXX)

set(SRC
    main.cpp
    src/server_file.cpp
    src/ServerHandlerSystem.cpp
    src/UDPServer.cpp
    src/ServerCore.cpp
    src/GameLogicSystem.cpp
    src/LevelManagement.cpp
    src/ScoreManager.cpp
    src/MovementSystem.cpp
    src/CollisionSystem.cpp
)

add_executable(r-type_server ${SRC})

target_link_libraries(r-type_server PRIVATE ECS)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(r-type_server
    PUBLIC
        ECS Systems
)
