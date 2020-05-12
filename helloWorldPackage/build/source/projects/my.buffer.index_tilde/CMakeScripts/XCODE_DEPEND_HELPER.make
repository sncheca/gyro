# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.my.buffer.index_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.buffer.index_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.buffer.index_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/MinSizeRel/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~


PostBuild.my.buffer.index_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/externals/RelWithDebInfo/my.buffer.index~.mxo/Contents/MacOS/my.buffer.index~




# For each target create a dummy ruleso the target does not have to exist
