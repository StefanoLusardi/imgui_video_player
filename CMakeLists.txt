cmake_minimum_required(VERSION 3.16)
project(tiny_video_player VERSION 0.1.0)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/modules)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(tiny_video_player)
add_subdirectory(tiny_video_decoder)
