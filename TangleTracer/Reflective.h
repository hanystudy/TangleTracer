// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once


#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective: public Phong {	
	public:
	
		Reflective(void);										

		Reflective(const Reflective& rm);						

		Reflective& 
		operator= (const Reflective& rhs);						

		virtual Reflective*										
		clone(void) const;				

		~Reflective(void);										
		
		void
		set_kr(const float k);
				
		void													
		set_cr(const RGBColor& c);
		
		void
		set_cr(const float r, const float g, const float b);
		
		void
		set_cr(const float c);
		
		virtual RGBColor										
		shade(ShadeRec& s);

		virtual RGBColor
		area_light_shade(ShadeRec& sr);		//This function doesn't appear in book, but needed by 24.43
		
		virtual RGBColor
		global_shade(ShadeRec& sr);	//new for c26

		virtual RGBColor
		path_shade(ShadeRec& sr);	//new for c26

	private:
	
		PerfectSpecular* reflective_brdf;		
};


// ---------------------------------------------------------------- set_kr

inline void
Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const RGBColor& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}
