#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/min-api/test/mock -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/min-api/test/mock/CMakeScripts/mock_kernel_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
