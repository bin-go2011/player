cmake_minimum_required(VERSION 3.0)
project(player)

add_definitions(-g3 -std=c++14 -D__STDC_CONSTANT_MACROS 
                -Wall -Wextra -Wextra -pedantic 
                -Wdisabled-optimization -Wctor-dtor-privacy -Wmissing-declarations 
                -Woverloaded-virtual -Wshadow -Wno-unused -Winline 
)

include_directories(
    /usr/local/Cellar/sdl2/2.0.8/include
    /usr/local/Cellar/ffmpeg/4.0.1/include
)
link_directories(
    /usr/local/Cellar/sdl2/2.0.8/lib
    /usr/local/Cellar/ffmpeg/4.0.1/lib
)

file(GLOB CPP_SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)
# list(REMOVE_ITEM CPP_SOURCES ${CMAKE_SOURCE_DIR}/ffmpeg.cpp)
message(${CPP_SOURCES})
add_executable(player ${CPP_SOURCES})
target_link_libraries(player avformat avcodec avutil swscale SDL2 pthread)
