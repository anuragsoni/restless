file(GLOB SRC_FILES *.cpp)
include_directories(${RESTLESS_INCLUDE_DIRS}
                    ${CURL_INCLUDE_DIRS})
add_library(${RESTLESS_LIBRARIES} ${SRC_FILES})
target_link_libraries(${RESTLESS_LIBRARIES} ${CURL_LIBRARIES})

install (TARGETS restless DESTINATION bin)
install (FILES ${SRC_HEADER} DESTINATION include)
