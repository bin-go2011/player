cmake_minimum_required(VERSION 3.0)
project(player)

add_definitions(-g3 -std=c++14 -D__STDC_CONSTANT_MACROS 
                -Wall -Wextra -Wextra -pedantic 
                -Wdisabled-optimization -Wctor-dtor-privacy -Wmissing-declarations 
                -Woverloaded-virtual -Wshadow -Wno-unused -Winline 
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(FFmpeg REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${FFMPEG_INCLUDE_DIRS}
)

file(GLOB CPP_SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)
# list(REMOVE_ITEM CPP_SOURCES ${CMAKE_SOURCE_DIR}/ffmpeg.cpp)
add_executable(player ${CPP_SOURCES})
target_link_libraries(player ${FFMPEG_LIBRARIES} ${SDL2_LIBRARY} ${SWSCALE_LIBRARIES})
