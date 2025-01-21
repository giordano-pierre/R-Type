cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(r-type VERSION 1.0 LANGUAGES CXX)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
    message(STATUS "Targeting Windows 10+ (_WIN32_WINNT=0x0A00)")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)

if(NOT nlohmann_json_FOUND)
    message(FATAL_ERROR "nlohmann_json library not found. Please ensure it's installed via vcpkg.")
endif()

if(MSVC)
    add_compile_options(-W3)
    message(STATUS "Configured MSVC with warnings level 3 and no warnings as errors.")
else()
    # add_compile_options(-Wall -Wextra -Wno-error)
    message(STATUS "Configured GCC/Clang with moderate warnings and no errors.")
endif()

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

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
