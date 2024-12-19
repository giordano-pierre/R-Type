cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(r-type VERSION 1.0 LANGUAGES CXX)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

add_subdirectory(lib)
add_subdirectory(serveur)
add_subdirectory(client)
add_subdirectory(tests)

add_custom_target(assets SOURCES
    assets/audio
    assets/font
    assets/images
)
