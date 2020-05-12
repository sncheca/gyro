# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.my.phasor_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test


PostBuild.my.phasor_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test


PostBuild.my.phasor_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test


PostBuild.my.phasor_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.phasor_tilde_test




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
