// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// An open cylinder is defined by its extent in the y direction and its radius.
// It is centered on the y axis.
// The classes ConcaveOpenCylinder and ConvexOpenCylinder can inherit from ConvexOpenCylinder.
// The classes ConcavePartCylinder and ConvexPartCylinder can in turn inherit from these.

#pragma once

#include "GeometricObject.h"
#include <math.h>

class ConvexOpenCylinder: public GeometricObject {
	
	public:
		
		ConvexOpenCylinder(void);   									

		ConvexOpenCylinder(const double bottom, const double top, const double radius);

		ConvexOpenCylinder(const ConvexOpenCylinder& c); 					
		
		virtual ConvexOpenCylinder* 									
		clone (void) const;

		ConvexOpenCylinder& 											
		operator= (const ConvexOpenCylinder& rhs);		
		
		virtual 												
		~ConvexOpenCylinder(void);
						
		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& sr) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin) const;
		
	protected:
	
		double		y0;				// bottom y value
		double		y1;				// top y value
		double		radius;			// radius
		double		inv_radius;  	// one over the radius	
};
