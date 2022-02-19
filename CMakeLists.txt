cmake_minimum_required(VERSION 3.21)
project(circular_buffer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp CircularBuffer.hpp)

if(ENABLE_TESTING)
    set(Boost_USE_STATIC_LIBS ON)
    find_package(
        Boost 1.66 REQUIRED
        COMPONENTS unit_test_framework
    )
    target_link_libraries(${PROJECT_NAME} Boost::unit_test_framework)
endif()
