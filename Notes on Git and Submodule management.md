# Notes on Git and Submodule management

This projects makes use of submodules. [This is the best online resource](https://www.atlassian.com/git/tutorials/git-submodule) I have found about submodules. 

I set up the `min-devkit` to be a submodule. The idea here is that the user should not actually modify the `min-devkit`, but will definitely need to reference it often. Also, creating new packages bootstraps off of the `min-devkit`, as outlined in [How to Create a New Package](https://github.com/Cycling74/min-devkit/blob/a14f4080d564132125a3a90b12309bade19907f8/HowTo-NewPackage.md) from Cycling74. 

The min-devkit (and therefore all packages derived from it, including `gyro`), contains two submodules: the [min-api](https://github.com/Cycling74/min-api/tree/210d5da4b9a3ebc201b4be5c1f0733e3110b1993) and the [min-lib](https://github.com/Cycling74/min-lib/tree/fabb855b5c7534aec469ad891b9c5cb1d6e9468e). The `min-api` in turn contains a submodule [max-api](https://github.com/Cycling74/max-api/tree/1c06b88fc30da0931b6dfa4a874bc081afe00926). The advantage of using submodules is that if Cycling74 releases updates to any of these, then with a few simple commands, we can update the submodules without changing the entire structure of `gyro`. Note that submodules are locked to a particular commit and will not update automatically, which is good because updates to min submodules could potentially break `gyro` objects. Note also that when you follow [the build instructions provided by Cycling74](https://github.com/Cycling74/min-devkit/blob/master/ReadMe.md), the submodules get updated. 

Before you will be able to commit a package to your repo, you must `git add` it. Note that you must include the trailing slash, like this:

`git add pathToNewPackage/`