file(GLOB_RECURSE WAV_FILES "*.wav")

ADD_LIBRARY(binaural MODULE
    Binaural.cpp
    Binaural.h
    Binaural.exp
    BinauralVersion.h
    Fir.cpp
    Fir.h
    ${WAV_FILES}
)

find_package(Libsndfile)

IF (APPLE)    
    find_library(AUDIOUNIT_LIBRARY AudioUnit)
    FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation)

    TARGET_LINK_LIBRARIES(binaural
        ${COREAUDIO_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
        ${AUDIOUNIT_LIBRARY}
    )

    SET_TARGET_PROPERTIES(binaural PROPERTIES
        BUNDLE true
        BUNDLE_EXTENSION "component"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    )

    SET_SOURCE_FILES_PROPERTIES(
        ${WAV_FILES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )

ENDIF (APPLE)

set(Boost_USE_STATIC_LIBS ON) 
find_package(Boost COMPONENTS filesystem system container) 

TARGET_LINK_LIBRARIES(binaural
    core_audio
    ${LIBSNDFILE_LIBRARY}
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

INSTALL(TARGETS binaural
    DESTINATION "$ENV{HOME}/Library/Audio/Plug-Ins/Components"
)
