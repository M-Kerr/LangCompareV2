cmake_minimum_required(VERSION 3.0.0)
project(LangCompare VERSION 0.0.1)

# TODO I need to write a script that moves the src directory into the build
# directory

add_subdirectory(src/third_party/fmt/)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>/src)
