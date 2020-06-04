# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.gyro.speakerDecoder_tilde.Debug:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~


PostBuild.gyro.speakerDecoder_tilde.Release:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~


PostBuild.gyro.speakerDecoder_tilde.MinSizeRel:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/MinSizeRel/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~


PostBuild.gyro.speakerDecoder_tilde.RelWithDebInfo:
/Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~:
	/bin/rm -f /Users/sofia/Documents/GitHub/gyro/gyro/externals/RelWithDebInfo/gyro.speakerDecoder~.mxo/Contents/MacOS/gyro.speakerDecoder~




# For each target create a dummy ruleso the target does not have to exist
