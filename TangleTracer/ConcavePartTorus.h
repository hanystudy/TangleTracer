// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "GeometricObject.h"

class ConcavePartTorus: public GeometricObject {
	public:
		
		ConcavePartTorus(void);   									
		
		ConcavePartTorus(const double _a, const double _b, const double _min_azimuth, const double _max_azimuth, const double _min_polar, const double _max_polar);

		virtual ConcavePartTorus* 									
		clone(void) const;
	
		ConcavePartTorus(const ConcavePartTorus& torus);
		
		virtual
		~ConcavePartTorus(void); 											
		
		ConcavePartTorus& 
		operator= (ConcavePartTorus& rhs);	
		
		Normal 					
		compute_normal(const Point3D& p) const;  												
		
		virtual bool 																 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool 																						 
		shadow_hit(const Ray& ray, float& tmin) const;
		
	private:
	
		double 		a;	 	// swept radius 
		double		b;	 	// tube radius
		double min_azimuth;	
		double max_azimuth;	
		double min_polar;	
		double max_polar;	
		BBox		bbox;	// the bounding box
};
