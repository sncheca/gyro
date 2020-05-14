# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.binauralDecoder_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.encoder_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.hello-world.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.Debug:
PostBuild.mock_kernel.Debug: /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test


PostBuild.gyro.soundfield2stereo_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.thru_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.mock_kernel.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib


PostBuild.gyro.binauralDecoder_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.encoder_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.hello-world.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.Release:
PostBuild.mock_kernel.Release: /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/gyro.hello-world_test


PostBuild.gyro.soundfield2stereo_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.thru_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.mock_kernel.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib


PostBuild.gyro.binauralDecoder_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.encoder_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.hello-world.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.MinSizeRel:
PostBuild.mock_kernel.MinSizeRel: /Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/gyro.hello-world_test


PostBuild.gyro.soundfield2stereo_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.thru_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.mock_kernel.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib


PostBuild.gyro.binauralDecoder_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.encoder_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.hello-world.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.hello-world.mxo/Contents/MacOS/gyro.hello-world


PostBuild.gyro.hello-world_test.RelWithDebInfo:
PostBuild.mock_kernel.RelWithDebInfo: /Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test
/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test:\
	/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/gyro.hello-world_test


PostBuild.gyro.soundfield2stereo_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.thru_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.mock_kernel.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib




# For each target create a dummy ruleso the target does not have to exist
/Users/sofia/Documents/GitHub/gyro/gyro/tests/MinSizeRel/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/RelWithDebInfo/libmock_kernel.dylib:
/Users/sofia/Documents/GitHub/gyro/gyro/tests/libmock_kernel.dylib:
