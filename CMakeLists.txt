cmake_minimum_required(VERSION 3.21)
project(ciricullar_buffer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp CiricullarBuffer.hpp)

if(ENABLE_TESTING)
    find_package(
        Boost 1.66 REQUIRED
        COMPONENTS unit_test_framework
    )
    target_link_libraries(${PROJECT_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()
