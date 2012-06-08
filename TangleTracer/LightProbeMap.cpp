// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "LightProbeMap.h"

// ---------------------------------------------------------------- default constructor

LightProbeMap::LightProbeMap(void) {

	map_type = light_probe;
}


// ---------------------------------------------------------------- copy constructor

LightProbeMap::LightProbeMap(const LightProbeMap& sm):map_type(sm.map_type) {}
	
	
// ---------------------------------------------------------------- assignment operator

LightProbeMap& 
LightProbeMap::operator= (const LightProbeMap& rhs) {
	if (this == &rhs)
		return (*this);

	map_type = rhs.map_type;

	return (*this);
}


// ---------------------------------------------------------------- destructor

LightProbeMap::~LightProbeMap (void) {} 


// ---------------------------------------------------------------- clone

LightProbeMap*								
LightProbeMap::clone(void) const {
	return (new LightProbeMap(*this));
}	


// ---------------------------------------------------------------- get_texel_coordinates

// Given a hit point on a generic sphere, and the image resolution, this function 
// returns the texel coordinates in the image

void
LightProbeMap::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
										const 	int 		xres, 
										const 	int 		yres, 
												int& 		row, 
												int& 		column) const {
	
	float x = local_hit_point.x; 
	float y = local_hit_point.y; 
	float z = local_hit_point.z;
	
	float d = sqrt(x * x + y * y);
	float sin_beta = y / d;
	float cos_beta = x / d;       
	float alpha;
	
	if (map_type == light_probe)   // the default
		alpha = acos(z);
		
	if (map_type == panoramic)
		alpha = acos(-z);
	
	float r = alpha * invPI;     		
	float u = (1.0 + r * cos_beta) * 0.5;
	float v = (1.0 + r * sin_beta) * 0.5;
	column 	= (int) ((xres - 1) * u);	
	row 	= (int) ((yres - 1) * v);
}
