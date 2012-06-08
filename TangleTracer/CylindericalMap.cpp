// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "CylindericalMap.h"

// ---------------------------------------------------------------- default constructor

CylindericalMap::CylindericalMap(void) {}


// ---------------------------------------------------------------- copy constructor

CylindericalMap::CylindericalMap(const CylindericalMap& sm) {}
	
	
// ---------------------------------------------------------------- assignment operator

CylindericalMap& 
CylindericalMap::operator= (const CylindericalMap& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

CylindericalMap::~CylindericalMap (void) {} 


// ---------------------------------------------------------------- clone

CylindericalMap*								
CylindericalMap::clone(void) const {
	return (new CylindericalMap(*this));
}	


// ---------------------------------------------------------------- get_texel_coordinates

// Given a hit point on a generic sphere, and the image resolution, this function 
// returns the texel coordinates in the image

void
CylindericalMap::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
										const 	int 		xres, 
										const 	int 		yres, 
												int& 		row, 
												int& 		column) const {
	
	// first, compute theta and phi

	float phi   = atan2(local_hit_point.x, local_hit_point.z);
	if (phi < 0.0)
		phi += TWO_PI;
	
	// next, map theta and phi to (u, v) in [0, 1] X [0, 1]
		
	float u = phi * invTWO_PI;    
	float v = local_hit_point.y;           
	// equation p651
			
	// finally, map u and v to the texel coordinates
		

	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int)  ((yres - 1) * v);    	// row is up
}
