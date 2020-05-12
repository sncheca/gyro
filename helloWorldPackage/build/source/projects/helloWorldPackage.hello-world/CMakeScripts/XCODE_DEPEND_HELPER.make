# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.helloWorldPackage.hello-world.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test


PostBuild.helloWorldPackage.hello-world.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test


PostBuild.helloWorldPackage.hello-world.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test


PostBuild.helloWorldPackage.hello-world.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
