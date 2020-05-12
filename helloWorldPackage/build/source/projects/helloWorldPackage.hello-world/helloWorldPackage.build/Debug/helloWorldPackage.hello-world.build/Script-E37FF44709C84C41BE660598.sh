#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/helloWorldPackage.hello-world -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/helloWorldPackage.hello-world/CMakeScripts/helloWorldPackage.hello-world_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
