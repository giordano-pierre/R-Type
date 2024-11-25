add_library(ECS STATIC
    src/some_ecs_file.cpp
    include/some_ecs_header.h
)

target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
