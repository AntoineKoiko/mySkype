##
## EPITECH PROJECT, 2021
## B-CPP-500-REN-5-1-bsbabel-aurelien.joncour
## File description:
## CmakeLists
##

cmake_minimum_required(VERSION 3.17)
add_definitions("-fPIC")

set(CMAKE_BUILD_TYPE Release)
set(NAME record)

project(${NAME} LANGUAGES CXX)

include_directories(./includes)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(${NAME})

set(SRCS
        src/main.cpp
        )

add_executable(${NAME} ${SRCS})

conan_target_link_libraries(${NAME} portaudio opus qt)