cmake_minimum_required(VERSION 2.8)

project(RESTLESS CXX)

# check for dependencies
find_package(CURL REQUIRED)

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# set up include path
include_directories(${CURL_INCLUDE_DIRS} include)

# set up source directory
add_subdirectory(src)

# set up tests
enable_testing()
add_executable(restless_unit test/unit.cpp)
target_link_libraries(restless_unit
    restless
    ${CURL_LIBRARIES}
    pthread
)
add_test(unitTest restless_unit)