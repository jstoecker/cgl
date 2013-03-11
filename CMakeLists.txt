# CGL CMake File
# Justin Stoecker

cmake_minimum_required(VERSION 2.8)
project(CGL)

# main directory
source_group("" FILES cgl.h)
install(FILES cgl.h DESTINATION include/cgl)

# gl subdirectory
file(GLOB SRC_GL gl/*.cc gl/*.h)
source_group("gl" FILES ${SRC_GL} ${INC_GL})
install(DIRECTORY gl DESTINATION include/cgl FILES_MATCHING PATTERN "*.h")

# math subdirectory
file(GLOB SRC_MATH math/*.h)
source_group("math" FILES ${SRC_MATH})
install(DIRECTORY math DESTINATION include/cgl FILES_MATCHING PATTERN "*.h")

# util subdirectory
file(GLOB SRC_UTIL util/*.cc util/*.h)
source_group("util" FILES ${SRC_UTIL})
install(DIRECTORY util DESTINATION include/cgl FILES_MATCHING PATTERN "*.h")

include_directories(.)
add_library(cgl STATIC cgl.h ${SRC_GL} ${SRC_MATH} ${SRC_UTIL})
install(TARGETS cgl DESTINATION lib)
