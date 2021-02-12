cmake_minimum_required(VERSION 3.04)

project(LangCompareV2 VERSION 0.0.1 LANGUAGES CXX)

include_directories(src/)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR 
CMAKE_BUILD_TYPE STREQUAL "release"))
    option(PACKAGE_TESTS "Build the tests" ON)
endif()
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
