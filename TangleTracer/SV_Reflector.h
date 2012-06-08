// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Phong.h"
#include "PerfectSpecular.h"
#include "Texture.h"
#include "SV_PerfectSpecular.h"

class SV_Reflector: public Phong {	
	public:
	
		SV_Reflector(void);										

		SV_Reflector(const SV_Reflector& rm);						

		SV_Reflector& 
		operator= (const SV_Reflector& rhs);						

		virtual SV_Reflector*										
		clone(void) const;				

		~SV_Reflector(void);										
		
		void
		set_kr(const float k);
				
		void													
		set_cr(Texture* t_ptr);
		
		virtual RGBColor										
		shade(ShadeRec& s);

		virtual RGBColor
		area_light_shade(ShadeRec& sr);		//This function doesn't appear in book, but needed by 24.43
		
		virtual RGBColor
		global_shade(ShadeRec& sr);	//new for c26

		virtual RGBColor
		path_shade(ShadeRec& sr);	//new for c26

	private:
	
		//PerfectSpecular* reflective_brdf;		
		SV_PerfectSpecular* reflective_brdf;		
		Texture *texture_ptr;
};


// ---------------------------------------------------------------- set_kr

inline void
SV_Reflector::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}

inline void
SV_Reflector::set_cr(Texture* c) {
	reflective_brdf->set_cr(c);
}
