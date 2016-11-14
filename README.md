# VOSTOK - The Voxel Octree Solar Toolkit
VOSTOK is a command-line tool to compute a detailed model of incoming solar radiation distribution on a patch of land, including structures like buildings and vegetation, represented by a 3D point cloud data set. 

The program is written in C++ and makes use of the "SOLPOS.H" library to compute the angular position of the sun in the sky for a given location on earth and a given moment in time. SOLPOS.H was created by the U.S. Department of Energy National Renewable Energy Laboratory ( http://rredc.nrel.gov/solar/codesandalgorithms/solpos/ ) and released under the public domain.

VOSTOK works by transforming the input point cloud into a voxel volume with configurable resolution (voxel size). The voxels are represented as a sparse octree, and incoming sunlight and shadowing effects are simulated by raycasting on the voxel octree geometry. Raycasting is parallelized with OpenMP to make full use of multi-core processors.

## Building VOSTOK
In order to build VOSTOK, you need to have the GNU C++ compiler (g++) and GNU Make (or compatible tools) installed on your computer. Additional third-party libraries are not required.

The VOSTOK GitHub repository contains two folders "Debug" and "Release". Each folder contains a Makefile for a specific build configuration: In "Debug" configuration, additional information for debugging is compiled into the binary, but its computing performance is reduced. For productive use, it is recommended to use the faster "Release" configuration. 

To build VOSTOK with one of the two configurations, open your command prompt and navigate to the respective configuration folder. Then type "make" and hit [Return]. The program will now be built, and after a couple of seconds you should find a binary named "vostok" in the same folder.
