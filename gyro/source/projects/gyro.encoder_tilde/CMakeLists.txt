# Copyright 2018 The Min-DevKit Authors. All rights reserved.
# Use of this source code is governed by the MIT License found in the License.md file.

cmake_minimum_required(VERSION 3.0)

set(C74_MIN_API_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../min-api)
include(${C74_MIN_API_DIR}/script/min-pretarget.cmake)


#############################################################
# MAX EXTERNAL
#############################################################


include_directories( 
	"${C74_INCLUDES}"
)


set( SOURCE_FILES
	${PROJECT_NAME}.cpp
	${C74_MIN_API_DIR}/../resonance_audio/base/audio_buffer.cpp
    ${C74_MIN_API_DIR}/../resonance_audio/base/channel_view.cpp
    ${C74_MIN_API_DIR}/../resonance_audio/base/simd_utils.cpp
    ${C74_MIN_API_DIR}/../resonance_audio/ambisonics/associated_legendre_polynomials_generator.cpp
    ${C74_MIN_API_DIR}/../resonance_audio/base/spherical_angle.cpp
    
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
