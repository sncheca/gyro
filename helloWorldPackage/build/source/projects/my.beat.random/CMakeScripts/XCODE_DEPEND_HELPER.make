# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.my.beat.random.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test


PostBuild.my.beat.random.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test


PostBuild.my.beat.random.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test


PostBuild.my.beat.random.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
