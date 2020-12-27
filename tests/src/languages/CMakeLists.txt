package_add_test(code_tests code_tests.cpp ${PROJECT_NAME}_languages)
package_add_test(languages_tests languages_tests.cpp ${PROJECT_NAME}_languages)
# Copy python_module to test user-code module functionality for python
add_custom_command(TARGET languages_tests POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/tests/src/languages/py_packaging/
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/tests/code/py)

package_add_test(results_tests results_tests.cpp ${PROJECT_NAME}_languages)
