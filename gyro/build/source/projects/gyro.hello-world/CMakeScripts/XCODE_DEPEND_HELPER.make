# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.hello-world.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test


PostBuild.gyro.hello-world.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test


PostBuild.gyro.hello-world.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test


PostBuild.gyro.hello-world.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib:
