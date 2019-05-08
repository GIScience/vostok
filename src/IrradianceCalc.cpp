/*
 * OldCodeIrradianceCalc.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sebastian
 */

// TODO 2: Consider clear sky index in computations
// TODO 3: Was passiert mit reflected radiation im originalprogramm?
// TODO 3: Re-calculate SOLPOS results if a point is too far away from the last point for which they were computed
// TODO 4: Understand solposdata.interval. Can we make us of it?

// Required by MSVC to know math constants like "M_PI":
#define _USE_MATH_DEFINES

#include "IrradianceCalc.h"
#include <cmath>

/*
 * Required SOLPOS variables:
 *
 * elevetr
 * elevref
 * azim
 * daynum
 * amass
 *
 */
IrradianceCalc::IrradianceCalc(const posdata& solPosData) : m_solposData(solPosData) {
	
	/* 
	NOTE: Linke atmospheric turbidity coefficient is fixed to 3. This value is near 
	the annual average for rural-city areas in 	Europe, i.e. mild climate in the northern 
	hemispere (cf. https://grass.osgeo.org/grass77/manuals/r.sun.html ).
	The factor must be adapted for other study areas, see reference literature.
	*/
	m_linke = 3;

	m_elevEtr_rad = m_solposData.elevetr * (M_PI / 180);


	// Calculate extraterrestrial irradiation and direct irradiation normal to the solar beam.
	// These are not point-specific, so we only need to compute them once for each time and geographic location.

	// ATTENTION: getIrradianceBeamNormal needs m_irrET to be computed first, so don't change the order here!
	m_irrET = getIrradianceExtraTerrestrial(m_solposData.daynum);
	m_irrBeamNormal = getIrradianceBeamNormal();
	
	/*
	NOTE: in m_irrBeamNormal only the orthogonal, direct irradiance is calculated. 	This assumes *CLEAR SKY*.
	Covered sky is not modelled at the moment, cloud-free sky is assumed.
	For a correction of the modelling, measurements at meteo. stations could be used, by correcting based on 
	the *ratio between overcast and clear sky values*. This must be done individually for every study area.
	cf. Suri & Hofierka (2004): https://onlinelibrary.wiley.com/doi/pdf/10.1111/j.1467-9671.2004.00174.x
	
	TODO: The method to include diffuse irradiation is implemented in this function (see below):
		double IrradianceCalc::getIrradiance(const std::vector<double>& p, bool illuminated)
		https://github.com/GIScience/vostok/blob/16b7cff32f1603f7411906e41cb27bdb23699238/src/IrradianceCalc.cpp#L55
	
		!!! It is not used in the current version of VOSTOK !!!
	*/

}

IrradianceCalc::~IrradianceCalc() {
	// TODO Auto-generated destructor stub
}


double IrradianceCalc::getIrradiance(const std::vector<double>& p, bool illuminated) {

	// TODO: Don't hard-code array indices for the normal vector. Make this user-configurable!
	Vec3d normal(p[3], p[4], p[5]);

	double aspect = getAspect(normal);
	double tilt = getSlope(normal);
	double cosinc = getIncidenceAngle(normal, m_solposData.azim, m_solposData.elevref);

	// Always add diffuse irradiation:
	double irradiation = getIrradianceDiffuse(aspect, tilt, cosinc);

	// Add beam irradiation only if point is not in shadow:
	if (illuminated) {
		irradiation += getIrradianceBeamInclined(aspect, tilt, cosinc);
	}

	return irradiation;
}


//############### BEGIN Static methods to compute aspect, incidence angle and slope ################
double IrradianceCalc::getAspect(const Vec3d& normal) {

	double a = 0.0 * normal.x() + 1.0 * normal.y();
	double b = sqrt(normal.x() * normal.x() + normal.y() * normal.y()) * 1;
	double cn = 0;

	if (b == 0.0) {
		cn = 0.0;		// in case of horizontal surface
	} else {
		cn = ((acos(a / b) * 180) / M_PI); //get angle in degree
		if (normal.x() < 0) {
			cn = 360. - cn;
		}
	}

	return cn;
}

double IrradianceCalc::getIncidenceAngle(Vec3d& normal, float azimuth, float elevation) {

	double elev = (90.0 - elevation) * M_PI / 180.0;
	double snX = 1.0 * sin(azimuth * M_PI / 180.) * sin(elev); // normal vectors from azimuth angle and elevation angle
	double snY = 1.0 * cos(azimuth * M_PI / 180.) * sin(elev);
	double snZ = 1.0 * cos(elev);  // for z vector

	//sun in nadir
	if (elevation == 90.0) {
		snX = 0;
		snY = 0;
		snZ = 1;
	}

	double r = (normal.x() * normal.x()) + (normal.y() * normal.y()) + (normal.z() * normal.z());
	double len_sn = snX * snX + snY * snY + snZ * snZ;
	double inprod = normal.x() * snX + normal.y() * snY + normal.z() * snZ;
	double cosangle = inprod / sqrt(r * len_sn);
	return cosangle;  // returning the cosine of incidence angle.
}

double IrradianceCalc::getSlope(const Vec3d& normal) {

	double c = 0;
	double dx = sqrt(normal.x() * normal.x() + normal.y() * normal.y());
	double dy = normal.z();

	if (dx == 0) {
		c = 0.0;
	} else {
		c = fabs(atan(dy / dx)) * 180.0 / M_PI;
		c = 90.0 - c; // slope of surface is 90 minus slope of normal vector
	}
	return c;
}
//############### BEGIN Static methods to compute aspect, incidence angle and slope ################

//############## BEGIN Methods for computation of different types of IRRADIANCE ###############


double IrradianceCalc::getIrradianceBeamInclined(double aspect, double tilt, double cosinc) {

	double beamRad = 0.;
	double incDeg = acos(cosinc) * 180.0 / M_PI;

	//fprintf(stdout, "cos: %.3f tilt %.3f aspect %.3f incidence: %.3f\n", acos(varData->cosinc)*180.0/M_PI, varData->tilt, varData->aspect, acos(incidenceAngle)*180.0/M_PI);
	//it means plane is in shadow or before sunrise or after sunset

	if (m_solposData.elevref < 0 && incDeg > 90.0) {
		beamRad = 0.0; // there is no direct radiation in shadow and before sunrise and after sunset
	} else {
		// bew and kc are taken from Suncalculator file from beamRad() method
		//these variables are used to calculate beam radiance on horizontal / vertical surface
		double bew = (0 * 0.8) / 8;
		double kc = 1 - (0.75 * pow(bew, 3.4));
		double nbr = m_irrBeamNormal;

		if (tilt < 5) {
			beamRad = nbr * kc * sin(m_elevEtr_rad);
		} // beam radiation on horizontal surface but we use always normal vector (azim/slope)
		else {
			//incidenceAngle;
			// on inclined surface incidenceAngle as cosine = sin((M_PI/2.0) - acos(incidenceAngle))
			// as we measure incidence angle to normal vector
			beamRad = nbr * kc * cosinc;
		}
	}

	if (beamRad < 0.0) {
		beamRad = 0.0;
	}

	return beamRad;
}

/**
 * Get irradiance normal to the solar beam
 * ATTENTION: This requires m_irrET to be computed first!
 */
double IrradianceCalc::getIrradianceBeamNormal() {

	double airMass = m_solposData.amass;

	// this is linke to airmass turbidity factor
	double tlk = 0.8662 * m_linke;
	double rayleighThickness = 0;

	//as written in paper by Hofierka and Suri
	//calculates reyleigh optical thickness at air mass given by airMass variable

	if (airMass <= 20) {
		rayleighThickness = 1.0 / (6.6296 + airMass * (1.7513 + airMass * (-0.1202 + airMass * (0.0065 - airMass * 0.00013))));
	} else {
		rayleighThickness = 1.0 / (10.4 + 0.718 * airMass); // if airmass is greater than 20
	}

	//beam Irradiance normal to solar beam and returns the double value to calling mehtod
	return m_irrET * exp(-tlk * airMass * rayleighThickness);
}

double IrradianceCalc::getIrradianceDiffuse(double aspect, double tilt, double cosinc) {

	double tn, fd, a1, a2, a3, a4, fx = 0;  //, gh;
	double kb, rs, aln, ln, fg, diffrad = 0.;
	//value for linke variable is taken from Suncalculator file
	double cosSlope, sinSlope;
	//taken from SunCalculator file
	double bew = (0 * 0.8) / 8;
	double kc = 1 - (0.75 * pow(bew, 3.4));
	//double alb = 0.2;   // for reflected radiation

	// This is Tn_T_LK:
	tn = -0.015843 + m_linke * (0.030543 + 0.0003797 * m_linke); //theoretical diffuse irradiance on a horizontal surface with for the air mass 2 Linke turbidity

	//calculating a4 which in turn determines how to cal a,a1 , a2 for fd calculaiton
	//taken from Hofeirka and suri paper
	a4 = 0.26463 + m_linke * (-0.061581 + 0.0031408 * m_linke);

	//as done in Hofeirka and suri paper
	if ((a4 * tn) < 0.0022) {
		a1 = 0.0022 / tn;
	} else {
		a1 = a4;
	}

	a2 = 2.04020 + m_linke * (0.018945 - 0.011161 * m_linke);
	a3 = -1.3025 + m_linke * (0.039231 + 0.0085079 * m_linke);

	//getting tilt value in radian and h0 value from elevref field of struct into radian
	double pointTilt = tilt * M_PI / 180;

	cosSlope = cos(pointTilt); // cos of tilt
	sinSlope = sin(pointTilt);  // sin of tilt; tilt is in radian

	//calculaitng solar altitude function
	fd = a1 + a2 * sin(m_elevEtr_rad) + a3 * sin(m_elevEtr_rad) * sin(m_elevEtr_rad);

	//calculaitng the irradiance on horizontal surface
	double hsr = m_irrET * fd * tn; //  on horizontal plane
	double bRad = m_irrBeamNormal * sin(m_elevEtr_rad); //beam radiation

	//gh = hsr + bRad; // adding beam radiaiton and extra terrestrial radiance
	//calculaitng the solar radiation on inlcined surface

	//double rr = 0;

	//formula used has been taken from paper
	// it is for inclined surface
	if (pointTilt >= 0.1) {

		kb = bRad / (m_irrET * sin(m_elevEtr_rad)); //kb is amount of normal beam radiaiton available
		rs = (1. + cosSlope) / 2.;

		aln = ((m_solposData.azim * M_PI / 180)) - (aspect * M_PI / 180);
		ln = aln;

		if (aln > M_PI) {
			ln = aln - (2. * M_PI);
		} else if (aln < -M_PI) {
			ln = aln + (2. * M_PI);
		}

		aln = ln;
		fg = sinSlope - pointTilt * cosSlope - M_PI * sin(pointTilt / 2.) * sin(pointTilt / 2.);

		// shadow
		if (cosinc < 0) {
			fx = rs + fg * 0.252271;
		} else if (m_elevEtr_rad >= 0.1) {
			fx = ((0.00263 - kb * (0.712 + 0.6883 * kb)) * fg + rs) * (1. - kb) + kb * (sin(M_PI / 2 - acos(cosinc)) / sin(m_elevEtr_rad));
		} else if (m_elevEtr_rad < 0.1) {
			fx = ((0.00263 - 0.712 * kb - 0.6883 * kb * kb) * fg + rs) * (1. - kb)
					+ kb * sinSlope * cos(aln) / (0.1 - 0.008 * m_elevEtr_rad);
		}

		diffrad = kc * hsr * fx;

		//rr = alb * gh * (1 - cos(pointTilt)) / 2.; // getting reflected radiation value
		// it is not added to global radiation value
	}

	else // horizontal plane
	{
		diffrad = kc * hsr;
		//rr = 0.;  // reflected radiaiton is zero
	}

	//there is no radiation before sunrise and after sunset
	//if(varData->elevref <= 0.0 || diffrad<0)
	if (diffrad < 0) {
		diffrad = 0;
		//rr = 0;
	}
	return diffrad;
}

double IrradianceCalc::getIrradianceExtraTerrestrial(int dayNum) {

	double j = (2. * M_PI) * dayNum / 365.25; //day angle in radians

	//correction factor due to sun-earth distance varies across the year
	double G0 = 1 + 0.03344 * cos(j - 0.048869);
	//extra terrestrial calculation

	return (1367. * G0); //calculating in WM-2 unit
}

//############## END Methods for computation of different types of IRRADIANCE ###############
