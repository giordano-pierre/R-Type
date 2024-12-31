add_library(Shared INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/enums.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/events/ReceiveEvent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/events/RequestEvent.hpp
)

target_include_directories(Shared INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
