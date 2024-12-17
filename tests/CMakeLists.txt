enable_testing()

add_executable(UnitTest unit_test.cpp)

target_link_libraries(UnitTest PRIVATE ECS Systems)

add_test(NAME UnitTest COMMAND UnitTest)
