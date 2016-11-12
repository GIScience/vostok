# vostok
VOSTOK, The Voxel Octree Solar Toolkit, is a command-line tool to compute a detailed model of incoming solar radiation distribution on a patch of land, including structures like buildings and vegetation, represented by a 3D point cloud data set. 

The program is written in C++ and makes use of the "SOLPOS.H" library to compute the angular position of the sun in the sky for a given location on earth and moment in time. SOLPOS.H was created by the U.S. Department of Energy National Renewable Energy Laboratory ( http://rredc.nrel.gov/solar/codesandalgorithms/solpos/ ) and released under the public domain.

VOSTOK works by transforming the input point cloud into a voxel volume with configurable resolution (voxel size). The voxels are represented as a sparse octree, and incoming sunlight and shadowing effects are simulated by raycasting on the voxel octree geometry. Raycasting is parallelized with OpenMP to make full use of multi-core processors.
