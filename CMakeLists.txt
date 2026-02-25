cmake_minimum_required(VERSION 3.23)
project(GestionBanque)


# For editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile options
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
add_compile_options(-Wall -Wextra -Wpedantic)

# Link
add_link_options(
    -static-libstdc++
    -static-libgcc
)

add_executable(GestionBanque)

target_sources(GestionBanque
    PRIVATE
        main.cpp
        cvm_23.cpp
)
