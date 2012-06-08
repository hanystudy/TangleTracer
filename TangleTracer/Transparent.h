// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Phong.h"
#include "PerfectSpecular.h"
#include "PerfectTransmitter.h"


class Transparent: public Phong {	
	public:

		Transparent(void);											

		Transparent(const Transparent& m);
		
		virtual Material*										
		clone(void) const;									

		Transparent& 
		operator= (const Transparent& rhs);							

		~Transparent(void);											
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	
		// constructors, etc ...

		virtual RGBColor										
		shade(ShadeRec& sr);	

		void
		set_ior(const float ior);		
		
		void
		set_kr(const float kr);
		
		void
		set_kt(const float kt);
	private:

		PerfectSpecular* 	reflective_brdf;
		PerfectTransmitter* specular_btdf;	
};

inline void
Transparent::set_ior(const float ior) {
	specular_btdf->set_ior(ior);
}
		
inline void
Transparent::set_kr(const float kr) {
	reflective_brdf->set_kr(kr);
}
		
inline void
Transparent::set_kt(const float kt) {
	specular_btdf->set_kt(kt);
}