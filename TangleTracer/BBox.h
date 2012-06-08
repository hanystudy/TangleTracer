// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Ray.h"
#include "Point3D.h"

class BBox {
	public:
		double x0, x1, y0, y1, z0, z1;
		
		BBox(void);										
						
		BBox(	const double x0, const double x1,			
				const double y0, const double y1, 
				const double z0, const double z1);

		BBox(const Point3D p0, const Point3D p1);											

		BBox(const BBox& bbox);							

		BBox& 												
		operator= (const BBox& rhs);			

		~BBox(void);										
		
		bool 															
		hit(const Ray& ray) const;
	
		bool
		inside(const Point3D& p) const;
};
