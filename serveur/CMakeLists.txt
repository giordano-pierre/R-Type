project(r-type_server VERSION 1.0 LANGUAGES CXX)

set(SRC
    main.cpp
    src/server_file.cpp
)

add_executable(r-type_server ${SRC})

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
