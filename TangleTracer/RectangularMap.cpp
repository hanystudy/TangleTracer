// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "RectangularMap.h"

// ---------------------------------------------------------------- default constructor

RectangularMap::RectangularMap(void) {}


// ---------------------------------------------------------------- copy constructor

RectangularMap::RectangularMap(const RectangularMap& sm) {}
	
	
// ---------------------------------------------------------------- assignment operator

RectangularMap& 
RectangularMap::operator= (const RectangularMap& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

RectangularMap::~RectangularMap (void) {} 


// ---------------------------------------------------------------- clone

RectangularMap*								
RectangularMap::clone(void) const {
	return (new RectangularMap(*this));
}	


// ---------------------------------------------------------------- get_texel_coordinates

// Given a hit point on a generic sphere, and the image resolution, this function 
// returns the texel coordinates in the image

void
RectangularMap::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
										const 	int 		xres, 
										const 	int 		yres, 
												int& 		row, 
												int& 		column) const {
		
	//equation P650

	float u = (local_hit_point.z + 1) / 2.0 ;
	float v = (local_hit_point.x + 1) / 2.0 ;
			
	// finally, map u and v to the texel coordinates
		
	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int)  ((yres - 1) * v);    	// row is up
}
