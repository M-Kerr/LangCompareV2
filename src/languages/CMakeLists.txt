add_library(${PROJECT_NAME}_languages
    STATIC
    results.cpp
    code.cpp
    code_cpp.cpp
    code_python.cpp
    languages.cpp
    )

target_link_libraries(${PROJECT_NAME}_languages
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${PROJECT_NAME}_helpers
    )
