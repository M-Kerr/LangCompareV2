package_add_test(code_tests code_tests.cpp ${PROJECT_NAME}_languages)
package_add_test(languages_tests languages_tests.cpp ${PROJECT_NAME}_languages)

# Copy python_module to test user-code module functionality for python
add_custom_target(test_py_code_files ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/src/languages/test_code/py/
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/code/py)

# Copy python_module to test user-code module functionality for cpp
add_custom_target(test_cpp_code_files ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/src/languages/test_code/cpp/
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/code/cpp)

package_add_test(results_tests results_tests.cpp ${PROJECT_NAME}_languages)
