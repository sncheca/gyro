# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.thru.index_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~


PostBuild.gyro.thru.index_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~


PostBuild.gyro.thru.index_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~


PostBuild.gyro.thru.index_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.thru.index~.mxo/Contents/MacOS/gyro.thru.index~




# For each target create a dummy ruleso the target does not have to exist
