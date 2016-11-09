

#ifndef OLDCODEIRRADIANCECALC_H_
#define OLDCODEIRRADIANCECALC_H_

#include "Vec3d.h"
#include "solpos/solpos00.h"
#include "pointCloud/AbstractPointCloud.h"
#include <vector>

class IrradianceCalc {

public:
	IrradianceCalc(const posdata& solPosData);

	virtual ~IrradianceCalc();


	double getIrradiance(const std::vector<double>& point, bool illuminated);

protected:

	// TODO 4: Get rid of Vec3d here
	static double getAspect(const Vec3d& normal);
	static double getIncidenceAngle(Vec3d& normal, float azimuth, float elevation);
	static double getSlope(const Vec3d& normal);



	double getIrradianceBeamInclined(double aspect, double tilt, double cosinc);
	double getIrradianceBeamNormal();

	double getIrradianceDiffuse(double aspect, double tilt, double cosinc);

	static double getIrradianceExtraTerrestrial(int dayNum);

	// TODO 3: Don't copy this
	posdata m_solposData;



	double m_elevEtr_rad;
	double m_linke;

	double m_irrET;
	double m_irrBeamNormal;

};

#endif /* OLDCODEIRRADIANCECALC_H_ */
