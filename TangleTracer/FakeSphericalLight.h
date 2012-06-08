// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// The FakeSpeericalLight is from exercise 18.1, which simulate soft shadows with a point light

#pragma once

#include "Light.h"
#include "ShadeRec.h"

#include "Maths.h"

//Notice that location in the book should be Point3D type, not Vector3D

class FakeSphericalLight: public Light {	
	public:
		
		FakeSphericalLight(void);   							

		FakeSphericalLight(const FakeSphericalLight& dl); 
		
		virtual Light* 									
		clone(void) const;			

		FakeSphericalLight& 									
		operator= (const FakeSphericalLight& rhs); 
			
		virtual											
		~FakeSphericalLight(void); 
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 		
		
		void
		set_location(const Point3D& l);

		void
		set_location(const float x, const float y, const float z);

		virtual Vector3D
		get_direction(ShadeRec& sr);

		virtual RGBColor
		L(ShadeRec& sr);

		void
		scale_radiance(const float b);

		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;

		void
		set_jitter_amount(float radius);

		void 
		use_distance_attenuation(bool b);

	private:
		
		float 		ls;
		RGBColor 	color;
		Point3D 	location;
		
		float jitter_amount;
		bool distance_attenuation;
};


// inlined access functions


// ------------------------------------------------------------------------------- set_color

inline void
FakeSphericalLight::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}
		
inline void
FakeSphericalLight::set_color(const RGBColor& c)
{
	color = c;
}
		
inline void
FakeSphericalLight::set_color(const float r, const float g, const float b)
{
	color.r = r; color.g = g; color.b = b;
}

inline void 
FakeSphericalLight::set_location(const float x, const float y, const float z)
{
	location = Point3D(x,y,z);
}

inline void 
FakeSphericalLight::set_jitter_amount(float radius)
{
	this->jitter_amount = radius;
}

inline void 
FakeSphericalLight::use_distance_attenuation(bool b)
{
	distance_attenuation = b;
}