# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.my.edge_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test


PostBuild.my.edge_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test


PostBuild.my.edge_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test


PostBuild.my.edge_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
