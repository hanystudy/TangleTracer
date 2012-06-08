// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "JitteredDirectional.h"

// ---------------------------------------------------------------------- default constructor

JitteredDirectional::JitteredDirectional(void)
	: 	Directional(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0),
		r(0)
{}


// ---------------------------------------------------------------------- dopy constructor

JitteredDirectional::JitteredDirectional(const JitteredDirectional& dl)
	: 	Directional(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir),
		r(dl.r)
{}


// ---------------------------------------------------------------------- clone

Light* 
JitteredDirectional::clone(void) const {
	return (new JitteredDirectional(*this));
}


// ---------------------------------------------------------------------- assignment operator

JitteredDirectional& 
JitteredDirectional::operator= (const JitteredDirectional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;
	r = rhs.r;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

JitteredDirectional::~JitteredDirectional(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
JitteredDirectional::get_direction(ShadeRec& sr) {
	
	Vector3D finaldir;

	finaldir.x = dir.x + r * (2.0 * rand_float() - 1.0);
	finaldir.y = dir.y + r * (2.0 * rand_float() - 1.0);
	finaldir.z = dir.z + r * (2.0 * rand_float() - 1.0);
	
	finaldir.normalize();
	return (finaldir);
}	

// ------------------------------------------------------------------------------  L

RGBColor
JitteredDirectional::L(ShadeRec& s) {	
	return (ls * color);
}

bool									
JitteredDirectional::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t = 10000;	//this is very important
	int num_objects = sr.w.objects.size();
	double d = kEpsilon;
														
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t > d)
			return (true);
														
	return (false);
}
