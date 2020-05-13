# Copyright 2018 The Min-DevKit Authors. All rights reserved.
# Use of this source code is governed by the MIT License found in the License.md file.
# Updated for gyro by Sofia Checa in 2020

cmake_minimum_required(VERSION 3.0)

set(C74_MIN_API_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../min-api)
set(RESONANCE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../resonance_audio)
set(PITA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../pita)
include(${C74_MIN_API_DIR}/script/min-pretarget.cmake)


#############################################################
# MAX EXTERNAL
#############################################################


include_directories( 
	"${C74_INCLUDES}"
    "${RESONANCE_INCLUDES}"
    "${PITA_INCLUDES}"
)


set( SOURCE_FILES
	${PROJECT_NAME}.cpp
	${RESONANCE_INCLUDES}/base/audio_buffer.cpp
    ${RESONANCE_INCLUDES}/base/channel_view.cpp
    ${RESONANCE_INCLUDES}/base/simd_utils.cpp
    ${RESONANCE_INCLUDES}/ambisonics/stereo_from_soundfield_converter.cpp
    ${RESONANCE_INCLUDES}/dsp/gain.cpp
    
)


add_library( 
	${PROJECT_NAME} 
	MODULE
	${SOURCE_FILES}
)


include(${C74_MIN_API_DIR}/script/min-posttarget.cmake)


#############################################################
# UNIT TEST
#############################################################

include(${C74_MIN_API_DIR}/test/min-object-unittest.cmake)
