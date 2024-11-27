add_library(ECS STATIC
    src/ECS/ECS.cpp
    src/Entity/Entity.cpp
    include/ECS/ECS.hpp
    include/ECS/ECS.inl
    include/Entity/Entity.hpp
    include/Iterator/Iterator.hpp
    include/Iterator/Iterator.inl
    include/SparseArray/SparseArray.hpp
    include/SparseArray/SparseArray.inl
    include/Zipper/Zipper.hpp
    include/Zipper/Zipper.inl
)

target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
