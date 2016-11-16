# VOSTOK - The Voxel Octree Solar Toolkit
VOSTOK is a command-line tool to compute a detailed model of incoming solar radiation distribution on a patch of land, including structures like buildings and vegetation, represented by a 3D point cloud data set. 

The program is written in C++ and makes use of the "SOLPOS.H" library to compute the angular position of the sun in the sky for a given location on earth and a given moment in time. SOLPOS.H was created by the U.S. Department of Energy National Renewable Energy Laboratory ( http://rredc.nrel.gov/solar/codesandalgorithms/solpos/ ) and released under the public domain.

VOSTOK works by transforming the input point cloud into a voxel volume with configurable resolution (voxel size). The voxels are represented as a sparse octree, and incoming sunlight and shadowing effects are simulated by raycasting on the voxel octree geometry. Raycasting is parallelized with OpenMP to make full use of multi-core processors.

## Building VOSTOK
In order to build VOSTOK, you need to have the GNU C++ compiler (g++) and GNU Make (or compatible tools) installed on your computer. Additional third-party libraries are not required.

The VOSTOK GitHub repository contains two folders "Debug" and "Release". Each folder contains a Makefile for a specific build configuration: In "Debug" configuration, additional information for debugging is compiled into the binary, but its computing performance is reduced. For productive use, it is recommended to use the faster "Release" configuration. 

To build VOSTOK with one of the two configurations, open your command prompt and navigate to the respective configuration folder. Then type "make" and hit [Return]. The program will now be built, and after a couple of seconds you should find a binary named "vostok" in the same folder.

## Running VOSTOK

To run VOSTOK, you need to provide a .sol file containing information about the input files, the location of the scene, the time period for which the solar potential shall be calculated, etc.

An exemplary .sol file looks like this:

    example.xyz
    example.xyz
    1.0
    48.0
    16.0
    1
    2016
    1
    31
    1
    60
    1
    example_solPot_January2016.xyz
    1

The meaning of each line entry is as follows:

    line 1	File with points used for shadowing
    line 2	Point cloud for solar pot. calculation
    line 3	Voxel size for shadow voxels
    line 4	Latitude of scene in deci degrees
    line 5	Longitude of scene in deci degrees
    line 6	Time zone
    line 7	Year of calculation
    line 8	First day of calculation
    line 9	Last day of calculation
    line 10	Day step
    line 11	Minutes step
    line 12	Enable shadowing
    line 13	Output file name
    line 14	Enable multi threading

The input file (line 1) contains the points which are used for shadowing the scene.

The second file (line 2) corresponds to the points for which the solar potential is calculated. The file must contain xyz coordinates and normals nxnynz, each in subsequent columns seperated by blanks. Example with four points:

    78.750000 344.250000 40.615002 0.114376 0.220988 0.968547
    79.250000 344.250000 40.542000 0.063874 0.249720 0.966209
    79.750000 344.250000 40.520000 -0.196111 -0.040646 0.979739
    80.250000 344.250000 40.956001 -0.187723 -0.375608 0.907568
    
If the .sol file is adjusted and the input files are provided, run VOSTOK via

    vostok.exe example.sol

The tool will first generate a .vostokmeta file and then run the solar potential calculation. On your screen, somethin like the following messages should appear:

    ------------------------------------------------------
    Shadow points file path:      example.xyz
    Query points file path:       example.xyz
    Output file(s) path:          example_solPot_January2016.xyz
    Use Multithreading:           1
    
    Lat:                          48 degrees
    Lon:                          16 degrees
    Time Zone:                    1
    
    Year:                         2016
    Day Start:                    1
    Day End:                      31
    Days step:                    1
    Minutes step:                 60
    
    Shadow mode:                  1
    Shadow voxel size:            1 m
    ------------------------------------------------------
    
    
    No metafile for example.xyz found. Creating it...finished.
    
    Point cloud size:            270.5 x 170 x 68.084
    Required octree volume size: 512 x 512 x 512
    Required octree depth:       9
    
    Building octree... finished.
    
    Computing irradiation for each query point...
    
    Day   1   Sunrise: 07:51   Sunset:  16:06
    Day   2   Sunrise: 07:51   Sunset:  16:07
    Day   3   Sunrise: 07:51   Sunset:  16:08
    Day   4   Sunrise: 07:51   Sunset:  16:09
    Day   5   Sunrise: 07:51   Sunset:  16:10
    Day   6   Sunrise: 07:51   Sunset:  16:11
    Day   7   Sunrise: 07:51   Sunset:  16:13
    Day   8   Sunrise: 07:50   Sunset:  16:14
    Day   9   Sunrise: 07:50   Sunset:  16:15
    Day  10   Sunrise: 07:49   Sunset:  16:16
    Day  11   Sunrise: 07:49   Sunset:  16:17
    Day  12   Sunrise: 07:48   Sunset:  16:19
    Day  13   Sunrise: 07:48   Sunset:  16:20
    Day  14   Sunrise: 07:47   Sunset:  16:21
    Day  15   Sunrise: 07:47   Sunset:  16:23
    Day  16   Sunrise: 07:46   Sunset:  16:24
    Day  17   Sunrise: 07:45   Sunset:  16:26
    Day  18   Sunrise: 07:44   Sunset:  16:27
    Day  19   Sunrise: 07:44   Sunset:  16:28
    Day  20   Sunrise: 07:43   Sunset:  16:30
    Day  21   Sunrise: 07:42   Sunset:  16:31
    Day  22   Sunrise: 07:41   Sunset:  16:33
    Day  23   Sunrise: 07:40   Sunset:  16:34
    Day  24   Sunrise: 07:39   Sunset:  16:36
    Day  25   Sunrise: 07:38   Sunset:  16:38
    Day  26   Sunrise: 07:37   Sunset:  16:39
    Day  27   Sunrise: 07:36   Sunset:  16:41
    Day  28   Sunrise: 07:34   Sunset:  16:42
    Day  29   Sunrise: 07:33   Sunset:  16:44
    Day  30   Sunrise: 07:32   Sunset:  16:45
    Day  31   Sunrise: 07:31   Sunset:  16:47

The resulting file will contain the initial xyz coordinates, the nxnynz normals, and a new column with the calculated solar potential in Watt hours per square meter and day, summed up for the respective point.
