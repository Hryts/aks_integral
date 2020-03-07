cmake_minimum_required(VERSION 3.12)
project(acs_1_reading_speed_test)

set(CMAKE_CXX_STANDARD 17)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(integral main.cpp calculator.cpp read_config.cpp)
