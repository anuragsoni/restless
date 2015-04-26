file(GLOB SRC_FILES *.cpp)
file(GLOB SRC_HEADER *.hpp)
add_library(restless_lib
${SRC_FILES}
${SRC_HEADER})

install (TARGETS restless_lib DESTINATION bin)
install (FILES ${SRC_HEADER} DESTINATION include)