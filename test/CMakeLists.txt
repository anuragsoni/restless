macro(add_restless_test _TEST_NAME)
    add_executable(${_TEST_NAME}_test
        ${_TEST_NAME}.cpp)
    target_link_libraries(${_TEST_NAME}_test
        restless)
    add_test(NAME restless_${_TEST_NAME}_test COMMAND ${_TEST_NAME}_test)
endmacro()

include_directories(get_unit_test
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/ext/catch/single_include
        ${PROJECT_SOURCE_DIR}/ext/json/src)

add_restless_test(get)
add_restless_test(post)
add_restless_test(put)
add_restless_test(delete)
