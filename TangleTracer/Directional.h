// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include "World.h"			// you will need this later on for shadows
#include "ShadeRec.h"


class Directional: public Light {
	public:
	
		Directional(void);   							

		Directional(const Directional& dl); 
		
		virtual Light* 									
		clone(void) const;			

		Directional& 									
		operator= (const Directional& rhs); 
			
		virtual											
		~Directional(void); 
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 		
			
		void
		set_direction(Vector3D d);						
		
		void
		set_direction(float dx, float dy, float dz);
		
		virtual Vector3D								
		get_direction(ShadeRec& sr);
				
		virtual RGBColor		
		L(ShadeRec& sr);	
		
		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;	//add 

	private:

		float		ls;			
		RGBColor	color;
		Vector3D	dir;		// direction the light comes from
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
Directional::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


// ---------------------------------------------------------------------- set_direction

inline void
Directional::set_direction(Vector3D d) {
	dir = d;
	dir.normalize();
}


// ---------------------------------------------------------------------- set_direction 

inline void
Directional::set_direction(float dx, float dy, float dz) {
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}
