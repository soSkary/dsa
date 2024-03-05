cmake_minimum_required(VERSION 3.24)
set(main_executable dsa)
project(dsa LANGUAGES CXX)

option(USE_G++ "Use g++ as compiler" ON)
option(USE_A_SAN "Use address sanitizer" OFF)
option(USE_M_SAN "Use memory sanitizer" OFF)

#Choose which compiler g++ or clang++
if (USE_G++)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
else()
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
    add_compile_options(-stdlib=libc++)
endif()

#Address sanitizer
if (USE_A_SAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

#Memory sanitizer, doesn't work on g++
if (USE_M_SAN AND NOT USE_G++)
    add_compile_options(-fsanitize=memory)
    add_link_options(-fsanitize=memory)
endif()


add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(${main_executable} main.cpp)
target_include_directories(${main_executable} PUBLIC ${CMAKE_SOURCE_DIR}/include)

