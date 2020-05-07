# gyro
A MaxMSP wrapper for Google Resonance. A treat for your ears. Gyro because, well, it's a wrap that supports spinning functions. 

## Libraries and SDKs included

1. This wrapper utilizes the Cycling74's min-devkit, which can be found here: link to min-devkit: https://github.com/Cycling74/min-devkit
2. The sounds you hear are powered by Google Resonance. [insert link]

#Using Gyro

# Using min-devkit

Important: There must be an alias for the min-devkit folder in the Max 8/Packages folder. 

##Creating a new Package
can use the max interface to do this. extras >> Min >> C++ Object Development Kit.maxpat. 

## Modifying an Object
- make sure that the brick is checked under "Target Membership" in Xcode before compiling. 
- note that the actual updates to the object come from the .xml file in the doc folder
- this file is only created when you create the first instance of the object. If, within one Max session, you delete all instances and then make a new one, THIS DOES NOT COUNT. If you have an instance in a patch and then close and reopen the patch, THIS DOES NOT COUNT. The only thing that counts is opening a max patch (devoid of instances) and then instantiating the first one. Only then will the .xml file be updated. 

## Adding source files
As of now, I put the resonance_audio folder into the min_api/include directory. Then, in the cmakelists for each object, I link to there. This avoids having multiple copies of c++ files running around. When they pop up as source files, then they can be built into .o files and baked into new code!

## Audio buffers
Note that frames, as defined by Min, are basically just samples. So framecount() is the number of samples in each block. 
Also, note that, although the documentation says that samples() is a vector, IT IS NOT! It is a double*
