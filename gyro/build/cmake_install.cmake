# Install script for directory: /Users/sofia/Documents/GitHub/gyro/gyro

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/min-api/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/min-lib/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.binauralDecoder_tilde/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.encoder_tilde/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.hello-world/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.rotator_tilde/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.soundfield2stereo_tilde/cmake_install.cmake")
  include("/Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.thru_tilde/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/sofia/Documents/GitHub/gyro/gyro/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
