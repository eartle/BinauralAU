file(GLOB_RECURSE DIFFUSE_WAV_FILES "../res/diffuse/*.wav")
file(GLOB_RECURSE HRTF_DB_WAV_FILES "../res/RAW/WAV/*.wav")

ADD_LIBRARY(Binaural MODULE
    Binaural.cpp
    Binaural.h
    BinauralVersion.h
    Fir.cpp
    Fir.h
    Utils.m
    Utils.h
    ${DIFFUSE_WAV_FILES}
    ${HRTF_DB_WAV_FILES}
)

SET_SOURCE_FILES_PROPERTIES(
    Utils.m
    PROPERTIES
    COMPILE_FLAGS "-x objective-c++"
)

find_package(Libsndfile)

IF (APPLE)    
    FIND_LIBRARY(AUDIOUNIT_LIBRARY AudioUnit)
    FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY(FOUNDATION_LIBRARY Foundation)
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation)

    TARGET_LINK_LIBRARIES(Binaural
        ${COREAUDIO_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
        ${FOUNDATION_LIBRARY}
        ${AUDIOUNIT_LIBRARY}
    )

    SET_TARGET_PROPERTIES(Binaural PROPERTIES
        BUNDLE true
        BUNDLE_EXTENSION "component"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    )

    SET_SOURCE_FILES_PROPERTIES(
        ${DIFFUSE_WAV_FILES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/diffuse"
    )

    SET_SOURCE_FILES_PROPERTIES(
        ${HRTF_DB_WAV_FILES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/hrtfdb"
    )
ENDIF (APPLE)

set(Boost_USE_STATIC_LIBS ON) 
find_package(Boost COMPONENTS filesystem system container) 

TARGET_LINK_LIBRARIES(Binaural
    core_audio
    ${LIBSNDFILE_LIBRARIES}
    ${Boost_LIBRARIES}
)

INCLUDE_DIRECTORIES(.
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBSNDFILE_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/../ext/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/OtherBases"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ext/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/AUBase"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ext/CoreAudioUtilityClasses/CoreAudio/AudioUnits/AUPublic/Utility"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ext/CoreAudioUtilityClasses/CoreAudio/PublicUtility"
)

INSTALL(TARGETS Binaural
    DESTINATION "$ENV{HOME}/Library/Audio/Plug-Ins/Components"
)
