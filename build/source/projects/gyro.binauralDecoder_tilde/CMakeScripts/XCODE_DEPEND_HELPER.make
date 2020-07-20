# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.binauralDecoder_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.binauralDecoder_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.binauralDecoder_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/externals/MinSizeRel/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/MinSizeRel/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~


PostBuild.gyro.binauralDecoder_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/externals/RelWithDebInfo/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/externals/RelWithDebInfo/gyro.binauralDecoder~.mxo/Contents/MacOS/gyro.binauralDecoder~




# For each target create a dummy ruleso the target does not have to exist
