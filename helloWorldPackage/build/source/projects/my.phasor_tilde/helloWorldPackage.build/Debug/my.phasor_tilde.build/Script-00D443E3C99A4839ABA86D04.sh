#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.phasor_tilde -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.phasor_tilde/CMakeScripts/my.phasor_tilde_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
