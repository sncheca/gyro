#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.beat.random -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.beat.random/CMakeScripts/my.beat.random_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
