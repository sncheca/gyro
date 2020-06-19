## Notes on these Matlab scripts

This directory is a modified version of the [`matlab/`] (https://github.com/resonance-audio/resonance-audio/tree/master/matlab) directory that comes with `resonance_audio_master`. I use the matlab scripts to process data from the [SADIE-I HRTF database](https://www.york.ac.uk/sadie-project/database_old.html), courtesy of The Audio Lab, University of York, UK (Cal Armstrong, Lewis Thresh, Gavin Kearney). 

Below I enumerate the changes that I made to the matlab scripts.   
1. [These changes](https://github.com/resonance-audio/resonance-audio/issues/35) to file path names (Error from Google).  
2. Got rid of all hard-coded path names that involved "Subject\_002" and replaced these so that the subjectID can be an argument to the `hrtf_data/sadie/loadsadie.m` and `hrtf_data/sadie/sadieshhrirs.m` functions. I also updated the testing files accordingly. In `hrtf_data/sadie/generatesadiehrirs.m`, I create a loop that loops through each subject and each ambisonic order to generate all the spherically-encoded head-related impulse responses (shhrirs).  
3. The spherical-encoding process works as follows: Each order is assigned a speaker configuration, one of [`symmetric_cube`, `symmetric_dodecahedron_faces`, `symmetric_lebedev26`, `symmetric_pentakis_dodecahedron`, `symmetric_pentakis_icosidodecahedron`]. The angles corresponding to these speaker configurations are found in the `.mat` files in `hrtf_data/sadie`. The script searches through the measurements in the database, parses the file titles to determine the angles, and if finds a match between a measured angle and an angle in the speaker configuration, it uses that angle. Critically, this method depends on the exact angles of the desired speaker configuration being present in the database. There is no interpolation or approximation. The dummy-head measurements (Subjects 1 and 2) are more exhaustive than the human measurements (Subjects 3 -20). As such, the human subject measurements do not include the exact angles that are used in the dodecahedron, used for second-order encodings. The makers of SADIE acknowledge this [here](https://www.york.ac.uk/sadie-project/Measurementconfig.html#humanheadang), [here](https://www.york.ac.uk/sadie-project/ambidecHumanMeas.html), and [here](https://www.york.ac.uk/sadie-project/ambidec_old.html). I created `symmetric_dodecahedron_almost.mat` which aims to come as close as possible to the original `symmetric_dodecahedron_faces.mat` using angle measurements that are present in the human subjects' databases. Since the encoding process takes the virtual speaker angles into account, this should not be a problem, and this won't be noticeable once the hrirs have been encoded into spherical harmonics, ie, soundfield / B-format.  
4. The tolerance of EPSILON = 0.01 in `hrtf_data/sadie/loadsadie.m` was violated in some of the 5th order human subject encodings. This occurs because of aliasing in the bit conversion process. I changed the toleranace to 0.0101 to silence this issue. 