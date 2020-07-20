# gyro
A MaxMSP wrapper for Google Resonance. A treat for your ears. Gyro because, well, it's a wrap that supports spinning functions. 

## Structure

## Prerequisites

## Building
1. Clone `gyro` from Github (TODO: insert link) (TODO: or download from inside of Max using the Package Manager). If you clone `gyro` to a destination other than Max's Packages folder, then you will need to make an alias to it in your Packages folder. The Packages folder can be found inside of your Max 8 folder which is inside of your user's Documents folder.
2. In the Terminal or Console app of your choice, change directories (cd) into the `gyro` directory you cloned/installed in step 1. Alternatively, just navigate to that folder in finder. 
3. If you want to build EVERYTHING (Xcode session plus Max externals) in one step, then run  
`./buildGyro -e`  
This will create a `build/` directory if it does not already exist and populate it with your Xcode project. Then it will create an `externals/` directory if it does not already exist and populate it with the `gyro` Max externals, or if the `externals/` directory already exists, it will simply update the `gyro` Max externals.  

	Alternatively, you can build _only_ the Xcode session by double-clicking on the `buildGyro` executable in finder _or_ by running 
`./buildGyro` from the `gyro` directory.  
Then, you can build the externals by opening the Xcode project from the newly generated "build" folder and using the GUI.


## Libraries and SDKs included

1. This wrapper utilizes the Cycling74's min-devkit, which can be found here: link to min-devkit: https://github.com/Cycling74/min-devkit
2. The sounds you hear are powered by Google Resonance. [insert link]

# Using Gyro

# Using min-devkit

Important: There must be an alias for the min-devkit folder in the Max 8/Packages folder. 

## Creating a new Package
can use the max interface to do this. extras >> Min >> C++ Object Development Kit.maxpat. 

## Modifying an Object
- make sure that the brick is checked under "Target Membership" in Xcode before compiling. 
- note that the actual updates to the object come from the .xml file in the doc folder
- this file is only created when you create the first instance of the object. If, within one Max session, you delete all instances and then make a new one, THIS DOES NOT COUNT. If you have an instance in a patch and then close and reopen the patch, THIS DOES COUNT. If you open a max patch (devoid of instances) and then instantiate a new object, this counts. Only then will the .xml file be updated. Quitting and restarting Max seems to do the trick for this. 
- Need to talk about the peculiarity of the double construction. See this [comment in the issues log](https://github.com/Cycling74/min-devkit/issues/106). 


## Adding include directories and source files from external libraries
This section is for those not familiar with `cmake`.  

The `resonance_audio/` folder is located in the `source/` directory. To include all the `.h` files from the Resonance (or the library of your choice), you can either  
1. write out each relative path verbatim [quick, but not elegant]  
2. [more elegant option] modify the `CMakeLists.txt` inside each object's project folder. This entails using `set()` to define a new include directory, adding this new directory to the list inside `include_directories()`, and then using this new variable in path names wherever needed in the CMakeLists.txt file. This approach allows you to use shorter, localized path names inside your source files and header files. 

You will need to compile and link some `.cpp` files from Resonance in each object. Do this by adding each `.cpp` file to the list of `SOURCE_FILES` and then include these `SOURCE_FILES` inside the `add_library()` function.  

See any of the CMakeLists.txt files (located in `gyro/gyro/source/projects/gyro.someDirectory/`) for examples on how to do this. 

## Audio buffers
Note that frames, as defined by Min, are basically just samples. So framecount() is the number of samples in each block. 
Also, note that, although the documentation says that samples() is a vector, IT IS NOT! It is a double*

## Attributions
This work was jointly funded by the [Yale Center for Collaborative Arts and Media](https://ccam.yale.edu/) and the [Yale Department of Music](https://yalemusic.yale.edu/). Special thanks to Professor Konrad Kaczmarek.  
All `min-devkit`, `min-api`, and `min-lib` code is the property of Cycling74. All `resonance_audio` code is the property of Google. All other code is the property of Sofia Checa, but may be used freely for any purpose, provided that Cycling74, Google, and Sofia are properly attributed. 

## Help and Contact
Please feel free to reach out to [email alias] with bugs, issues, questions, or anything else. 
