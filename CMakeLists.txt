##
## EPITECH PROJECT, 2021
## Jaimepascmake
## File description:
## pasdedesc
##

cmake_minimum_required(VERSION 3.17)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME babel)
set(NAME_SERVER babel_server)
set(NAME_CLIENT babel_client)

project(${NAME} VERSION 0.0.0 LANGUAGES CXX)

## INCLUDES
include_directories(./includes)
include_directories(./includes/client/Audio)

## CONAN (le barbare)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## SOURCES
set(SRCS_SERVER
        src/server/main.cpp
)

set(SRCS_CLIENT
        src/client/main.cpp
        src/client/Audio/AudioDecoder.cpp
        src/client/Audio/AudioEncoder.cpp
        src/client/Audio/SoundEncoded.cpp
        src/client/Audio/SoundFrameBuffer.cpp
        src/client/Audio/AudioInput.cpp
        src/client/Audio/AudioOutput.cpp
)
## Execs
add_executable(${NAME_SERVER} ${SRCS_SERVER})
add_executable(${NAME_CLIENT} ${SRCS_CLIENT})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(${NAME_SERVER} PRIVATE -Wall -Wextra)
    target_compile_options(${NAME_CLIENT} PRIVATE -Wall -Wextra)
endif ()

set_target_properties(${NAME_SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set_target_properties(${NAME_CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

target_link_libraries(${NAME_SERVER} ${CONAN_LIBS})
target_link_libraries(${NAME_CLIENT} ${CONAN_LIBS})
target_link_directories(${NAME_SERVER} PRIVATE ${CONAN_INCLUDE_DIRS})
target_link_directories(${NAME_CLIENT} PRIVATE ${CONAN_INCLUDE_DIRS})
