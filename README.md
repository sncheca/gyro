# gyro

![](gyro_logo.jpg)

A MaxMSP wrapper for Google Resonance. A treat for your ears. Gyro because, well, it's a wrap that supports spinning functions. 

If you would like to download pre-built Max externals, please go to the [gyro-Max-externals](https://github.com/sncheca/gyro-Max-externals/releases/tag/v0.1.0) repository.

## Structure and Dependencies
`gyro` is based on the `min-devkit`, which can be found [here](https://github.com/Cycling74/min-devkit). If you are interested in the code behind `gyro` I highly recommend also cloning the `min-devkit` and exploring that as well. However, `gyro` does not have any dependencies on the min-devkit. 

Like `min-devkit`, `gyro` depends on  

* `min-api`: a folder within the devkit containing all of the support files you will need to compile an external object written in modern C++.
*  `min-lib` contains building blocks, helper classes, and unit generators that may be useful in authoring C++ code for audio, video, and data processing.

These two `min` depencies are submodules. You can read more about submodules in [Notes on Git and Submodule management.md](Notes on Git and Submodule management.md)

In addition, `gyro` depends on [Google Resonance](https://resonance-audio.github.io/resonance-audio/), which is Google's open source ambisonics and spatial audio project. Resonance is available in many forms already, such as Unity, FMOD, DAW Plugin, etc, but for some reason, there wasn't a Max version, which is why I made `gyro`. `Gyro` uses the C++ source code that can be found [here](https://github.com/resonance-audio/resonance-audio). 

## Prerequisites

The other prerequisites are identical to those for the `min-devkit`, copy-pasted below. 

To build the externals in this package you will need some form of compiler support on your system.

* On the Mac this means Xcode 10 or 11 (you can get from the App Store for free).
* On Windows this means Visual Studio 2017 or 2019 (you can download a free version from Microsoft). The installer for Visual Studio 2017 offers an option to install Git, which you should choose to do.  

You will also need to install a recent version of CMake (version 3.10 or higher).

Note that as of August 2020, `gyro` is not officially supported for Windows. (TODO!)

## Building
1. Clone `gyro` from Github at https://github.com/sncheca/gyro (TODO: or download from inside of Max using the Package Manager). If you clone `gyro` to a destination other than Max's Packages folder, then you will need to make an alias to it in your Packages folder. The Packages folder can be found inside of your Max 8 folder which is inside of your user's Documents folder.
2. In the Terminal or Console app of your choice, change directories (cd) into the `gyro` directory you cloned/installed in step 1. 
3. If you want to build EVERYTHING (Xcode session plus Max externals) in one step, then run  
`./buildGyro -e`  
This will create a `build/` directory if it does not already exist and populate it with your Xcode project. Then it will create an `externals/` directory if it does not already exist and populate it with the `gyro` Max externals, or if the `externals/` directory already exists, it will simply update the `gyro` Max externals.  

	Alternatively, you can build _only_ the Xcode session by double-clicking on the `buildGyro` executable in finder _or_ by running 
`./buildGyro` from the `gyro` directory.  
Then, you can build the externals by opening the Xcode project from the newly generated "build" folder and using the GUI.

## Using
In order for Max to find the patches, they must be in the `Max 8/Packages` folder.
I prefer to just create an alias to the `gyro` repo and move this alias into the `Max 8/Packages` folder. You can create an alias by right clicking on the directory in finder and clicking "Make Alias".

## Demo
The demo file is too large to host on Github without paying for extra data for `git-lfs`. You can download the raw 30-channel multitrack file from [here](https://yalmust.yale.edu/gyro).

# For those building new code inspired by `gyro`, here are some tips:

## Building a new Object
See the `min-devkit`'s [HowTo-NewObject.md](https://github.com/Cycling74/min-devkit/blob/master/HowTo-NewObject.md).
 
## Modifying an Object
Here are a few things to keep in mind if you build new objects inspired by `gyro` objects:

- make sure that the brick is checked under "Target Membership" in Xcode before compiling. 
- note that the actual updates to the object come from the .xml file in the `doc/` folder
- this file is only created when you create the first instance of the object. You must quit and restart Max in order to see your changes take effect. 


## Adding include directories and source files from external libraries
This section is for those not familiar with `cmake`.  

The `resonance_audio/` folder is located in the `source/` directory. To include all the `.h` files from the Resonance (or the library of your choice), you can either  
1. write out each relative path verbatim [quick, but not elegant]  
2. [more elegant option] modify the `CMakeLists.txt` inside each object's project folder. This entails using `set()` to define a new include directory, adding this new directory to the list inside `include_directories()`, and then using this new variable in path names wherever needed in the CMakeLists.txt file. This approach allows you to use shorter, localized path names inside your source files and header files. 

You will need to compile and link some `.cpp` files from Resonance in each object. Do this by adding each `.cpp` file to the list of `SOURCE_FILES` and then include these `SOURCE_FILES` inside the `add_library()` function.  

See any of the CMakeLists.txt files (located in `gyro/gyro/source/projects/gyro.someDirectory/`) for examples on how to do this. 

## Audio buffers
You can read more about how `min` handles audio in [GuideToAudio.md](source/min-api/doc/GuideToAudio.md).

Note that frames, as defined by `min`, are just samples. So framecount() is the number of samples in each block. 
Also, note that although the documentation says that `samples()` is a `vector`, IT IS NOT! It is a `double*`

One major inconvenience of this project is that `min` and `Resonance` treat audio buffers differently, so every object must convert between audio buffer types. You can see how this is done [here] (source/pita/audio_buffer_conversion.h).

While it is a very boring object, `gyro.thru~` is a good place to start looking at audio processing. If you want to start with something more exciting, I'd recommend `gyro.encoder~`. Don't start with `gyro.rotator~`, it is full of messy angle conversions. 

## Min Oddities
- For historical and memory-related reasons, some objects are constructed twice-- once as a dummy object and once with the parameters filled in. You can read the discussion [here](https://github.com/Cycling74/min-devkit/issues/106). This pecularity caused some problems in debugging, especially with constructor initialiser lists, so it's great to be aware of it.  


## Attributions
This work was jointly funded by the [Yale Center for Collaborative Arts and Media](https://ccam.yale.edu/), the [Yale Department of Music](https://yalemusic.yale.edu/), and [Yale Blended Reality](https://blendedreality.yale.edu/). Special thanks to Professor Konrad Kaczmarek.  
All `min-devkit`, `min-api`, and `min-lib` code is the property of Cycling74. All `resonance_audio` code is the property of Google. All other code is the property of Sofia Checa, but may be used freely for any purpose, provided that Cycling74, Google, and Sofia are properly attributed. 

## Help
Please feel free to reach out here on Github with bugs, issues, questions, or anything else. Nothing is too small!
