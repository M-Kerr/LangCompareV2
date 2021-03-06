set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

##### Qt Setup #####

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

#qml directory contains QRC_FILES definition
add_subdirectory(qml/)
if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
      main.cpp
      ${QRC_FILES}
    )
else()
    set(CMAKE_MACOSX_BUNDLE ${APPLE})
    set(MACOSX_BUNDLE_INFO_PLIST
        ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${CMAKE_PROJECT_VERSION})
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${CMAKE_PROJECT_VERSION})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${PROJECT_NAME})
    set(MACOSX_BUNDLE_ICON_FILE LangCompareV2)
    set(MACOSX_BUNDLE_COPYRIGHT
        "Copyright © 2021 Milo D Kerr under GNU GENERAL PUBLIC LICENSE")

    add_executable(${PROJECT_NAME}
      main.cpp
      ${QRC_FILES}
    )
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

##### Project Setup #####
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)

##### Gather source dirs into libraries #####
add_subdirectory(helpers/)

set(SRC_DIRS languages)
foreach(DIR IN LISTS SRC_DIRS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
    list(APPEND SRC_LIBS ${PROJECT_NAME}_${DIR})
endforeach()

##### Build main #####
target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
  ${PROJECT_NAME}_helpers
  ${SRC_LIBS}
  )

# Copy code directory into build directory
add_custom_target(build_code_files ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/code
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/code)
