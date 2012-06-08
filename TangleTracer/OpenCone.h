// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// The OpenCone class is based on Excercise 19.12

#pragma once

#include "GeometricObject.h"
#include <math.h>

class OpenCone: public GeometricObject {
	
	public:
		
		OpenCone(void);   									

		OpenCone(const double radius, const double height);

		OpenCone(const OpenCone& c); 					
		
		virtual OpenCone* 									
		clone (void) const;

		OpenCone& 											
		operator= (const OpenCone& rhs);		
		
		virtual 												
		~OpenCone(void);
						
		virtual bool
		hit(const Ray& ray, double& t, ShadeRec& sr) const;

		virtual bool
		shadow_hit(const Ray& ray, float& tmin) const;
		
	protected:

		double h;
		double r;
};
