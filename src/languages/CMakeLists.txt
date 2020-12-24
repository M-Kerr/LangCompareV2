add_library(${PROJECT_NAME}_languages
    STATIC
    results.cpp
    code.cpp
    cpp_code.cpp
    python_code.cpp
    languages.cpp
    )

target_link_libraries(${PROJECT_NAME}_languages
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${PROJECT_NAME}_helpers
    )
