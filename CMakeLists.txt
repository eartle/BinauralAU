cmake_minimum_required (VERSION 2.8.11)
project (BINAURAL)

SET(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

SET(CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
SET(CORE_AUDIO_UTILITY_CLASSES_URL "https://developer.apple.com/library/ios/samplecode/CoreAudioUtilityClasses/CoreAudioUtilityClasses.zip")
SET(CORE_AUDIO_UTILITY_CLASSES_ZIP "${CMAKE_CURRENT_SOURCE_DIR}/ext/CoreAudioUtilityClasses.zip")

SET(HRTF_DB_1002_URL "ftp://ftp.ircam.fr/pub/IRCAM/equipes/salles/listen/archive/SUBJECTS/IRC_1002.zip")
SET(HRTF_DB_1002_ZIP "${CMAKE_CURRENT_SOURCE_DIR}/res/IRC_1002.zip")

if(NOT EXISTS ${CORE_AUDIO_UTILITY_CLASSES_ZIP})
    # We don't have the Core Audio Utility Classes zip file
    # so download and unzip it

    FILE(DOWNLOAD
        ${CORE_AUDIO_UTILITY_CLASSES_URL}
        ${CORE_AUDIO_UTILITY_CLASSES_ZIP}
        EXPECTED_MD5 "349f5cef32fb2507fd79e7c6f0735595"
        SHOW_PROGRESS
    )

    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E tar -x ${CORE_AUDIO_UTILITY_CLASSES_ZIP}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ext"
    )
endif()

if(NOT EXISTS ${HRTF_DB_1002_ZIP})
    FILE(DOWNLOAD
        ${HRTF_DB_1002_URL}
        ${HRTF_DB_1002_ZIP}
        EXPECTED_MD5 "0799158ec00862a52c37c9ef8a4bd795"
        SHOW_PROGRESS
    )

    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E tar x ${HRTF_DB_1002_ZIP}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res"
    )
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar x "${CMAKE_CURRENT_SOURCE_DIR}/res/diffuse.zip"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res"
)

SET(CMAKE_CXX_FLAGS "-Wno-deprecated")

add_subdirectory(ext)
add_subdirectory(src)