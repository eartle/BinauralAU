cmake_minimum_required (VERSION 2.8.11)
project (BINAURAL)

SET(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

add_subdirectory(CoreAudio)
add_subdirectory(src)