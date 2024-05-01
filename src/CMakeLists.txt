cmake_minimum_required(VERSION 3.20) 

project(logger VERSION 0.0.1
        DESCRIPTION "simple logger"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(LOGGER_FILES logger.cpp)
set(EXTERNAL_LIB_FILES termcolor.h)



add_library(logger STATIC ${LOGGER_FILES})

target_include_directories(logger PRIVATE ../lib/termcolor)