// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This class is used in 21.09a, which is used for BeveledWedge class

#pragma once

#include "GeometricObject.h"

class PartAnnulus: public GeometricObject {
	public:
		
		PartAnnulus(void);   									
		
		PartAnnulus(Point3D center, Normal normal, double inner_radius, double wall_thickness, double min_azimuth, double max_azimuth);

		virtual PartAnnulus* 									
		clone(void) const;
	
		PartAnnulus(const PartAnnulus& torus);
		
		virtual
		~PartAnnulus(void); 											
		
		PartAnnulus& 
		operator= (PartAnnulus& rhs);	
		
		Normal 					
		compute_normal(const Point3D& p) const;  												
		
		virtual bool 																 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		virtual bool 																						 
		shadow_hit(const Ray& ray, float& tmin) const;
		
	private:

		Point3D center;
		Normal normal;
		double inner_radius;
		double wall_thickness;

		double i_squared;
		double w_squared;

		double min_azimuth;
		double max_azimuth;

		BBox		bbox;	// the bounding box
};
