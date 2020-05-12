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


PostBuild.mock_kernel.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib


PostBuild.my.beat.random.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test


PostBuild.my.buffer.index_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.edge_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test


PostBuild.my.phasor_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test


PostBuild.helloWorldPackage.hello-world.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test


PostBuild.mock_kernel.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib


PostBuild.my.beat.random.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.beat.random_test


PostBuild.my.buffer.index_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.edge_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.edge_tilde_test


PostBuild.my.phasor_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/my.phasor_tilde_test


PostBuild.helloWorldPackage.hello-world.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test


PostBuild.mock_kernel.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib


PostBuild.my.beat.random.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.beat.random_test


PostBuild.my.buffer.index_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.edge_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.edge_tilde_test


PostBuild.my.phasor_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.phasor~.mxo/Contents/MacOS/my.phasor~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.phasor~.mxo/Contents/MacOS/my.phasor~


PostBuild.my.phasor_tilde_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/my.phasor_tilde_test


PostBuild.helloWorldPackage.hello-world.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/helloWorldPackage.hello-world.mxo/Contents/MacOS/helloWorldPackage.hello-world


PostBuild.helloWorldPackage.hello-world_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test


PostBuild.mock_kernel.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib


PostBuild.my.beat.random.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.beat.random.mxo/Contents/MacOS/my.beat.random:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.beat.random.mxo/Contents/MacOS/my.beat.random


PostBuild.my.beat.random_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.beat.random_test


PostBuild.my.buffer.index_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.edge_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.edge~.mxo/Contents/MacOS/my.edge~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.edge~.mxo/Contents/MacOS/my.edge~


PostBuild.my.edge_tilde_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test:\
	/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/my.edge_tilde_test


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
