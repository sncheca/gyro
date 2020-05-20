# Expressions of Angles of 3D space
Objects like the `encoder~` and the `rotator~` use 3D angles to place source or rotate the soundfield, respectively. 

3D angle protocols are always a huge source of confusion, because unfortunately they are not universal. Let me try to make this as clear as possible.

`gyro` supports 3 ways to express 3D angles. These are  
1. Quaternions  
2. Euler angles  
3. Axis-Angle  

## Jit-style angle expressions

Outwardly, all `gyro` objects obey the same ordering standards as `jit` objects. This means that:  
1. Quaternions are ordered `x, y, z, w`  
2. Euler angles are ordered `xyz`, where the `x` direction is up-down (pitch), the `y` direction is side-side (yaw), and the `z` direction is tilt (roll). This picture (modifed from [here](https://www.shutterstock.com/image-vector/aviation-concept-axis-movement-three-dimensional-191329868)) communicates this clearly.

![](rollPitchYaw.png)

Please note that jitter uses a **Right-Handed** coordinate System. Some VR headsets / headtracking use a **Left-Handed** coordinate system (and so does Unity). To use a Left-Handed Coordinated system with `gyro` objects, [TODO!!] Note that this capability is not supported in jitter. 

Please note that the _Rotate Order_ attribute in the inspector for `jit` objects just controls the _order_ in which the rotations are performed, but does _not_ change the order in which the angles are expressed. 

If you are only using the externals, but not looking at any of the underlying code, then you don't need to worry about any of the below. 

## Resonance-style angle expressions
Inside the code, all angle protocols are converted to the way _Resonance_ does it. This means that:  
1. Quaternions are ordered `w, x, y, z`  

