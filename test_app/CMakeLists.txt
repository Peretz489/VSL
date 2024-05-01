cmake_minimum_required(VERSION 3.20) 

project(testapp VERSION 0.0.1
        DESCRIPTION "simple logger tests"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_EXE main.cpp)
set(LOGGER_BUILD_DIR logger)

include_directories( ../src)

add_subdirectory(../src ${LOGGER_BUILD_DIR})

add_executable(testapp ${SOURCE_EXE})

target_link_libraries(testapp logger)