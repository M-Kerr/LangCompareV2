add_library(${PROJECT_NAME}_languages
    STATIC
    results.cpp
    code.cpp
    languages.cpp
    )

target_link_libraries(${PROJECT_NAME}_languages
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
    ${PROJECT_NAME}_helpers
    )
