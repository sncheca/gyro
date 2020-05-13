# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.soundfield2stereo_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.soundfield2stereo_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.soundfield2stereo_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~


PostBuild.gyro.soundfield2stereo_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.soundfield2stereo~.mxo/Contents/MacOS/gyro.soundfield2stereo~




# For each target create a dummy ruleso the target does not have to exist
