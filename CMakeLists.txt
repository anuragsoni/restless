cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME_STR restless)

project(${PROJECT_NAME_STR} CXX)

find_package(CURL REQUIRED)

# Enable C++11 features on gcc/clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
endif()

# Set source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${SRC_DIR})
include_directories(${SRC_DIR})


add_executable(${PROJECT_NAME_STR} main.cpp)
target_include_directories(${PROJECT_NAME_STR} PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME_STR}
                        restless_lib
                        ${CURL_LIBRARIES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(test_restless ${TEST_SRC_FILES})
target_link_libraries(test_restless
        restless_lib
        ${CURL_LIBRARIES}
        pthread
        )
enable_testing()
add_test(NAME test_restless COMMAND test_restless)