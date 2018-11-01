cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

project(vostok LANGUAGES CXX)

# Find external dependencies
find_package(OpenMP)

# Setup compiler flags
# Default is RELWITHDEBINFO
# Change on command line e.g. with "-DCMAKE_BUILD_TYPE=RELEASE"
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -DNDEBUG -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -Wall")

add_definitions( -std=c++0x -m64)

# Define vostok executable ###################
set(header_files
  src/IrradianceCalc.h
  src/myUtils.h
  src/OctreeRaycaster.h
  src/ProjectConfig.h
  src/ShadowCalc.h
  src/Vec3d.h
  src/octree/Octree.h
  src/octree/OctreeNode.h
  src/octree/OctreeNodeInfo.h
  src/pointCloud/AbstractPointCloud.h
  src/pointCloud/SimpleTextPointCloud.h
  src/solpos/solpos00.h
)

set(source_files
  src/main.cpp
  src/myUtils.cpp
  src/IrradianceCalc.cpp
  src/OctreeRaycaster.cpp
  src/ProjectConfig.cpp
  src/ShadowCalc.cpp
  src/Vec3d.cpp
  src/octree/Octree.cpp
  src/octree/OctreeNode.cpp
  src/octree/OctreeNodeInfo.cpp
  src/pointCloud/AbstractPointCloud.cpp
  src/pointCloud/SimpleTextPointCloud.cpp
  src/solpos/solpos.cpp
)

add_executable(vostok
  ${source_files}
  ${header_files} # Not required, but good for some IDEs
)

if(OPENMP_FOUND)
  set_target_properties(vostok PROPERTIES
    COMPILE_OPTIONS ${OpenMP_CXX_FLAGS}
    LINK_FLAGS ${OpenMP_CXX_FLAGS}
  )
endif()
##############################################

# Support installation
# Choose installation on command line with "-DCMAKE_INSTALL_PREFIX=/some/path"
include(GNUInstallDirs)

install(TARGETS vostok
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
