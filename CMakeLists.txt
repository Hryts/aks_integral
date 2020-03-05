cmake_minimum_required( VERSION 3.12 )
project( acs_1_reading_speed_test )

set( CMAKE_CXX_STANDARD 17 )

SET(CMAKE_CXX_FLAGS -pthread)

add_executable( main main.cpp calculator.cpp read_config.cpp)
