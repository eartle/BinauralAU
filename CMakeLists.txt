cmake_minimum_required (VERSION 2.8.11)
project (BINAURAL)

SET(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
SET(CORE_AUDIO_UTILITY_CLASSES_URL "https://developer.apple.com/library/ios/samplecode/CoreAudioUtilityClasses/CoreAudioUtilityClasses.zip")
SET(CORE_AUDIO_UTILITY_CLASSES_ZIP "${CMAKE_CURRENT_SOURCE_DIR}/ext/CoreAudioUtilityClasses.zip")

if(NOT EXISTS ${CORE_AUDIO_UTILITY_CLASSES_ZIP})
    file(DOWNLOAD
        ${CORE_AUDIO_UTILITY_CLASSES_URL}
        ${CORE_AUDIO_UTILITY_CLASSES_ZIP}
        EXPECTED_MD5 "349f5cef32fb2507fd79e7c6f0735595"
        SHOW_PROGRESS
    )
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar x ${CORE_AUDIO_UTILITY_CLASSES_ZIP}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ext"
)

add_subdirectory(ext)
add_subdirectory(src)