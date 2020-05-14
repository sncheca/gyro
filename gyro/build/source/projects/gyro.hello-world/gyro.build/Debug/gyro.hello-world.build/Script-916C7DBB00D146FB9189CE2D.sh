#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.hello-world -f /Users/sofia/Documents/GitHub/gyro/gyro/build/source/projects/gyro.hello-world/CMakeScripts/gyro.hello-world_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
