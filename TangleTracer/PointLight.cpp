// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PointLight.h"
#include "ShadeRec.h"
#include "World.h"
#include "Vector3D.h"

// ---------------------------------------------------------------------- default constructor

PointLight::PointLight(void)
	: 	Light(),
		ls(1.0),
		color(1.0)		
{}


// ---------------------------------------------------------------------- dopy constructor

PointLight::PointLight(const PointLight& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		location(dl.location)
{}


// ---------------------------------------------------------------------- clone

Light* 
PointLight::clone(void) const {
	return (new PointLight(*this));
}


// ---------------------------------------------------------------------- assignment operator

PointLight& 
PointLight::operator= (const PointLight& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	location = rhs.location;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

PointLight::~PointLight(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
PointLight::get_direction(ShadeRec& sr) {
	return ((location - sr.local_hit_point).hat());			//here use local_hit_point instead of hit_point
}	

// ------------------------------------------------------------------------------  L

RGBColor
PointLight::L(ShadeRec& s) {	
	return (ls * color);
}


// ------------------------------------------------------------------------------- set_location

void
PointLight::set_location(const Point3D& l) {
	location = l;
}

// ------------------------------------------------------------------------------- scale_radiance

void
PointLight::scale_radiance(const float b) { 
	ls = b;
}

bool									
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t = 10000;		// may be need an initialization
	int num_objects = sr.w.objects.size();
	double d = location.distance(ray.o);
														
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return (true); 
														
	return (false);
}
