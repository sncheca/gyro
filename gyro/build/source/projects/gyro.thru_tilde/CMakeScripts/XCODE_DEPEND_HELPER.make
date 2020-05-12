# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.thru_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.gyro.thru_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.gyro.thru_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru~.mxo/Contents/MacOS/gyro.thru~


PostBuild.gyro.thru_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru~.mxo/Contents/MacOS/gyro.thru~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru~.mxo/Contents/MacOS/gyro.thru~




# For each target create a dummy ruleso the target does not have to exist
