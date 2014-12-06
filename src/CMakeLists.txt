ADD_LIBRARY(binaural MODULE
    Binaural.cpp
    Binaural.h
    Binaural.hpp
    Binaural.r
    Binaural.exp
    BinauralVersion.h
    Fir.cpp
    Fir.h
    hrtf.h
)

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
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )

ENDIF (APPLE)

TARGET_LINK_LIBRARIES(binaural core_audio)

INCLUDE_DIRECTORIES(. ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../CoreAudio/AudioUnits/AUPublic/OtherBases
    ${CMAKE_CURRENT_SOURCE_DIR}/../CoreAudio/AudioUnits/AUPublic/AUBase
    ${CMAKE_CURRENT_SOURCE_DIR}/../CoreAudio/AudioUnits/AUPublic/Utility
    ${CMAKE_CURRENT_SOURCE_DIR}/../CoreAudio/PublicUtility
)

INSTALL(TARGETS binaural
    DESTINATION $ENV{HOME}/Library/Audio/Plug-Ins/Components
)
