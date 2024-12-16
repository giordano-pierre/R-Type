add_library(Systems STATIC
    test.cpp
)

target_include_directories(Systems PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/systems/include)
