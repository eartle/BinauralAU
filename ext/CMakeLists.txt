file(GLOB_RECURSE core_audio_SRC
    "*.h"
    "*.cpp"
)

ADD_LIBRARY(core_audio STATIC
    ${core_audio_SRC}
)

IF (APPLE)    
    FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation)

    TARGET_LINK_LIBRARIES(core_audio
        ${COREAUDIO_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
    )
ENDIF (APPLE)

INCLUDE_DIRECTORIES(. ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/OtherBases
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/AUBase
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/Utility
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/AUViewBase
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreAudioUtilityClasses/CoreAudio/PublicUtility
)