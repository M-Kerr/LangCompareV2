add_library(${PROJECT_NAME}_Languages
    STATIC
    results.cpp
    code.cpp
    cpp_code.cpp
    python_code.cpp
    )

target_link_libraries(${PROJECT_NAME}_Languages
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    )
