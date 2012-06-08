// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This class is used in 19.27ab and 19.29b

#pragma once

#include "GeometricObject.h"

class Annulus: public GeometricObject {
	public:
		
		Annulus(void);   									
		
		Annulus(Point3D center, Normal normal, double inner_radius, double wall_thickness);

		virtual Annulus* 									
		clone(void) const;
	
		Annulus(const Annulus& torus);
		
		virtual
		~Annulus(void); 											
		
		Annulus& 
		operator= (Annulus& rhs);	
		
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

		BBox		bbox;	// the bounding box
};
