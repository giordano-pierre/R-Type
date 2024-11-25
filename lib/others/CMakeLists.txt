add_library(Systems STATIC
    systems/some_system.cpp
    systems/some_system.h
)

target_include_directories(Systems PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/systems/include)
