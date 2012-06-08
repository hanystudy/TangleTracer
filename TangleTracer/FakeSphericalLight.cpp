// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "FakeSphericalLight.h"
#include "ShadeRec.h"
#include "World.h"
#include "Vector3D.h"

// ---------------------------------------------------------------------- default constructor

FakeSphericalLight::FakeSphericalLight(void)
	: 	Light(),
		ls(1.0),
		color(1.0),
		jitter_amount(0),
		distance_attenuation(false)
{}


// ---------------------------------------------------------------------- dopy constructor

FakeSphericalLight::FakeSphericalLight(const FakeSphericalLight& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		location(dl.location),
		jitter_amount(dl.jitter_amount),
		distance_attenuation(dl.distance_attenuation)
{}


// ---------------------------------------------------------------------- clone

Light* 
FakeSphericalLight::clone(void) const {
	return (new FakeSphericalLight(*this));
}


// ---------------------------------------------------------------------- assignment operator

FakeSphericalLight& 
FakeSphericalLight::operator= (const FakeSphericalLight& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	location = rhs.location;

	jitter_amount = rhs.jitter_amount;
	distance_attenuation = rhs.distance_attenuation;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

FakeSphericalLight::~FakeSphericalLight(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
FakeSphericalLight::get_direction(ShadeRec& sr) {

	float r = this->jitter_amount;//3.0;
	Point3D new_location;
	new_location.x = location.x + r * (2.0 * rand_float() - 1.0);
	new_location.y = location.y + r * (2.0 * rand_float() - 1.0);
	new_location.z = location.z + r * (2.0 * rand_float() - 1.0);
	
	return((new_location - sr.local_hit_point).hat());
	//return ((location - sr.local_hit_point).hat());			//here use local_hit_point instead of hit_point

}	

// ------------------------------------------------------------------------------  L

RGBColor
FakeSphericalLight::L(ShadeRec& s) {
	if( !distance_attenuation )
		return (ls * color);
	else
	{
		//Here we can use many attenuation functions, but for better viewing with arguments in 18.12a, we only use 1/d^2 finally
		double d = s.hit_point.distance(location);
		return (ls * color / (d*d) );		//distance attenuation
	}
}


// ------------------------------------------------------------------------------- set_location

void
FakeSphericalLight::set_location(const Point3D& l) {
	location = l;
}

// ------------------------------------------------------------------------------- scale_radiance

void
FakeSphericalLight::scale_radiance(const float b) { 
	ls = b;
}

bool									
FakeSphericalLight::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t = 10000;		// may be need an initialization
	int num_objects = sr.w.objects.size();
	double d = location.distance(ray.o);
														
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return (true);
	return (false);
}
