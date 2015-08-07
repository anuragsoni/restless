cmake_minimum_required(VERSION 2.8)

project(RESTLESS CXX)

if(NOT ${CMAKE_VERSION} LESS 3.2)
        set(CMAKE_CXX_STANDARD 14)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
        message(STATUS "Checking compiler flags for C++14 support.")
        include (CheckCXXCompilerFlag)
        check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
        check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
        if(COMPILER_SUPPORTS_CXX14)
                message(STATUS "C++14 is supported")
                if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
                else()
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
                endif()
        elseif(COMPILER_SUPPORTS_CXX11)
                message(STATUS "C++11 is supported")
                if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
                else()
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
                endif()
        else()
                message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11/14 support. Please use a different C++ compiler")
        endif()
endif()


# check for dependencies
find_package(CURL REQUIRED)

# set up include path
include_directories(${CURL_INCLUDE_DIRS} include)

# set up source directory
add_subdirectory(src)


macro(restless_option OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
    option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
    if(DEFINED ENV{${OPTION_NAME}})
        # Allow setting the option through an environment variable
        set(${OPTION_NAME} $ENV{${OPTION_NAME}})
    endif()
    if(${OPTION_NAME})
        add_definitions(-D${OPTION_NAME})
    endif()
    message(STATUS "  ${OPTION_NAME}: ${${OPTION_NAME}}")
endmacro()


message(STATUS "Restless CMake Options")
message(STATUS "=======================================================")

restless_option(BUILD_RESTLESS_TESTS "Set to ON to build restless tests." OFF)

# set up tests

if(BUILD_RESTLESS_TESTS)
    enable_testing()
    add_executable(restless_unit test/unit.cpp)
    target_link_libraries(restless_unit
        restless
        ${CURL_LIBRARIES}
        pthread
    )
    add_test(unitTest restless_unit)
endif()
