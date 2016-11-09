
#ifndef SHADOWCALCULATOR_H_
#define SHADOWCALCULATOR_H_

#include "octree/Octree.h"
#include "solpos/solpos00.h"
#include "Vec3d.h"
#include "pointCloud/AbstractPointCloud.h"

#include <vector>


class ShadowCalc {
public:
	ShadowCalc(AbstractPointCloud& shadowCloud, double voxelSize);
	virtual ~ShadowCalc();

	bool computeShadow(const posdata& solPosData, const std::vector<double>& point);

	Octree m_octree;

protected:
	std::vector<OctreeNodeInfo> raycast(Vec3d& rayStart, Vec3d& mRayDir);
};

#endif /* SHADOWCALCULATOR_H_ */
