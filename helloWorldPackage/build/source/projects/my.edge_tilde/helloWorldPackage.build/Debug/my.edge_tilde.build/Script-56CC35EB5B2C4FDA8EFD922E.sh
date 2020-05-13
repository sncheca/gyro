#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.edge_tilde -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/my.edge_tilde/CMakeScripts/my.edge_tilde_postBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
