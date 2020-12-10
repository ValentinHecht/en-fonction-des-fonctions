project(networld LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

# Activate C99 standard:
SET(CMAKE_C_COMPILER "gcc" )
SET(CMAKE_C_FLAGS "-std=c99" )
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra `pkg-config gtk+-3.0 --cflags` `pkg-config gtk+-3.0 --libs` -lm")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# project configuration :
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

add_executable(en-fonction-des-fonctions)
target_link_libraries()

#without cmake package... 
#include_directories(${PROJECT_SOURCE_DIR}/raylib/src)
#link_directories(${PROJECT_SOURCE_DIR}/raylib)
#target_link_libraries(nw-viewer raylib supportlib pbplots GL m pthread dl rt X11)
