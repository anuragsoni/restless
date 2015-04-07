file(GLOB SRC_FILES *.cpp)
file(GLOB SRC_HEADER *.hpp)
add_library(project_lib
${SRC_FILES}
${SRC_HEADER})

install (TARGETS project_lib DESTINATION bin)
install (FILES ${SRC_HEADER} DESTINATION include)