# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.encoder_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.encoder_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.encoder_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/externals/MinSizeRel/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/MinSizeRel/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~


PostBuild.gyro.encoder_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/externals/RelWithDebInfo/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/RelWithDebInfo/gyro.encoder~.mxo/Contents/MacOS/gyro.encoder~




# For each target create a dummy ruleso the target does not have to exist
