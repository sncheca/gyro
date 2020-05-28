#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.rotator_tilde -f /Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.rotator_tilde/CMakeScripts/gyro.rotator_tilde_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
