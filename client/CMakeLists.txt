cmake_minimum_required(VERSION 3.16)

project(r-type_client VERSION 1.0 LANGUAGES CXX)

set(SRC
    main.cpp
    src/client_file.cpp
    src/UDPClient.cpp
    src/ClientHandlerSystem.cpp
)

add_executable(r-type_client ${SRC})

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(r-type_client PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

target_link_libraries(r-type_client
    PUBLIC
        ECS Systems
)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
