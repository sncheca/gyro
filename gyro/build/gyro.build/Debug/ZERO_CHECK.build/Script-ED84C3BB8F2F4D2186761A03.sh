#!/bin/sh
make -C /Users/sofia/Documents/GitHub/gyro/gyro/build -f /Users/sofia/Documents/GitHub/gyro/gyro/build/CMakeScripts/ZERO_CHECK_cmakeRulesBuildPhase.make$CONFIGURATION OBJDIR=$(basename "$OBJECT_FILE_DIR_normal") all
