file(GLOB SRC_FILES *.cpp)

add_library(restless STATIC ${SRC_FILES})
target_link_libraries(restless ${CURL_LIBRARIES})

install (TARGETS restless DESTINATION bin)
install (FILES ${SRC_HEADER} DESTINATION include)