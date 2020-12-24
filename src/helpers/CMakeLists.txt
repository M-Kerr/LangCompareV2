add_library(${PROJECT_NAME}_helpers STATIC helpers.cpp)


target_link_libraries(${PROJECT_NAME}_helpers
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    )
