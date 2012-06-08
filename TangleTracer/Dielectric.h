// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Phong.h"

#include "FresnelReflector.h"
#include "FresnelTransmitter.h"

class Dielectric: public Phong {	
	public:

		Dielectric(void);											

		Dielectric(const Dielectric& m);
		
		virtual Material*										
		clone(void) const;									

		Dielectric& 
		operator= (const Dielectric& rhs);							

		~Dielectric(void);											
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	
		// constructors, etc ...

		virtual RGBColor										
		shade(ShadeRec& sr);	

		void
		set_eta_in(const double);
		
		void
		set_eta_out(const double);

		void
		set_cf_in(const RGBColor in);

		void
		set_cf_out(const RGBColor out);

		void
		set_shadows(bool b);
		
	private:
		
		RGBColor 			cf_in;			// interior filter color 
		RGBColor 			cf_out;			// exterior filter color
		
		FresnelReflector*	fresnel_brdf;
		FresnelTransmitter*	fresnel_btdf;

		bool shadows;
};



inline void 
Dielectric::set_eta_in(const double in)
{
	fresnel_brdf->set_eta_in(in);
	fresnel_btdf->set_eta_in(in);
}
		
inline void
Dielectric::set_eta_out(const double out)
{
	fresnel_brdf->set_eta_out(out);
	fresnel_btdf->set_eta_out(out);
}

inline void 
Dielectric::set_cf_in(const RGBColor in)
{
	this->cf_in = in;
}

inline void 
Dielectric::set_cf_out(const RGBColor out)
{
	this->cf_out = out;
}

inline void
Dielectric::set_shadows(bool b)
{
	shadows = b;
}