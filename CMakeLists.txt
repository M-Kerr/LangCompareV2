cmake_minimum_required(VERSION 3.14)

project(LangCompareV2 VERSION 0.0.1 LANGUAGES CXX)

include_directories(src/)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)


##### Testing #####
#if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#    include(CTest)
#endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(PACKAGE_TESTS "Build the tests" ON)
endif()
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
