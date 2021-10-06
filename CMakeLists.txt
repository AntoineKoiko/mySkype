##
## EPITECH PROJECT, 2021
## Jaimepascmake
## File description:
## pasdedesc
##

cmake_minimum_required(VERSION 3.17)
add_definitions("-fPIC")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME babel)
set(NAME_SERVER babel_server)
set(NAME_CLIENT babel_client)

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(${NAME} VERSION 0.0.0 LANGUAGES CXX)

## INCLUDES
include_directories(./includes)

## CONAN (le barbare)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(${NAME})

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

set(SRCS_SERVER
       src/server/Database/Contact.cpp
       src/server/Database/ContactHandler.cpp
       src/server/Database/User.cpp
       src/server/Database/UserHandler.cpp
       src/server/Database/DatabaseManager.cpp
       src/server/Database/DatabaseManagerError.cpp
       src/server/main.cpp
       src/server/commands.cpp
       src/server/utils.cpp
       src/server/AsioTCPServer.cpp
       src/server/AsioTCPCli.cpp
       src/server/BabelServer.cpp
)

set(SRCS_CLIENT
        src/client/main.cpp
        src/client/Audio/AudioError.cpp
        src/client/Audio/AudioDecoder.cpp
        src/client/Audio/AudioEncoder.cpp
        src/client/Audio/SoundEncoded.cpp
        src/client/Audio/SoundFrameBuffer.cpp
        src/client/Audio/AudioInput.cpp
        src/client/Audio/AudioOutput.cpp
        src/client/Windows/MyWindow.cpp
        src/client/Windows/LoginScreen.cpp
        src/client/Windows/HomeScreen.cpp
        src/client/Windows/TitledListWithButton.cpp
        src/client/Windows/CallHandler.cpp
        src/client/Windows/ContactHandler.cpp
        src/client/Windows/Contact.cpp
        src/client/Windows/ContactRequestWidget.cpp
        src/client/Windows/AddContactWidget.cpp
        src/client/Network/SoundPacketManager.cpp
        src/client/Network/Udp.cpp
        src/client/Windows/CallScreen.cpp
        src/client/Windows/ContactHandler.cpp
        src/client/Windows/ListStrWidget.cpp
        src/client/Network/DataPacketManager.cpp
        src/client/Network/TcpClient.cpp
        src/client/UserHandler.cpp
)

## Execs
add_executable(${NAME_SERVER} ${SRCS_SERVER})
add_executable(${NAME_CLIENT} ${SRCS_CLIENT})

## INCLUDES
target_include_directories(${NAME_SERVER} BEFORE PUBLIC ./includes/server)
target_include_directories(${NAME_SERVER} BEFORE PUBLIC ./includes/server/Database)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC ./includes/client)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC ./includes/client/Audio)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC ./includes/client/Windows)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC ./includes/client/Network)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(${NAME_SERVER} PRIVATE -Wall -Wextra)
    target_compile_options(${NAME_CLIENT} PRIVATE -Wall -Wextra)
endif ()

set_target_properties(${NAME_SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set_target_properties(${NAME_CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

target_link_libraries(${NAME_SERVER} ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
target_link_libraries(${NAME_CLIENT} ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
target_link_directories(${NAME_SERVER} PRIVATE ${CONAN_INCLUDE_DIRS})
target_link_directories(${NAME_CLIENT} PRIVATE ${CONAN_INCLUDE_DIRS})
