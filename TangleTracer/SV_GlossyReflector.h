// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This class is needed by 25p1

#pragma once

#include "SV_Phong.h"
#include "SV_GlossySpecular.h"
#include "SV_Lambertian.h"

class SV_GlossyReflector: public SV_Phong {	
	public:
	
		// contructors, etc ...
		SV_GlossyReflector(void);											

		SV_GlossyReflector(const SV_GlossyReflector& m);
		
		virtual Material*										
		clone(void) const;									

		SV_GlossyReflector& 
		operator= (const SV_GlossyReflector& rhs);							

		~SV_GlossyReflector(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);

		void
		set_cd(Texture* t_ptr);

		void
		set_exp(const float c);

		void																						
		set_ks(const float c);

		void
		set_cs(Texture* t_ptr);
	
		virtual RGBColor									
		shade(ShadeRec& s);	

		virtual void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		// constructors etc ...
	
		void											
		set_samples(const int num_samples, const float exp);
	
		void
		set_kr(const float k);

		void
		set_cr(Texture* t_ptr);	//this is new function where doesn't appear in book
	
		void													
		set_exponent(const float exp);
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);
	
	private:
	
		//SV_Lambertian*	ambient_brdf;
		//SV_Lambertian*	diffuse_brdf;


		SV_GlossySpecular* glossy_specular_brdf;
		//SV_GlossySpecular*	specular_brdf;
};

inline void
SV_GlossyReflector::set_samples(const int num_samples, const float exp) {
	glossy_specular_brdf->set_samples(num_samples, exp);	
}
	
inline void
SV_GlossyReflector::set_kr(const float k) {
	glossy_specular_brdf->set_ks(k);
}
	
inline void
SV_GlossyReflector::set_exponent(const float exp) {
	glossy_specular_brdf->set_exp(exp);
}

inline void
SV_GlossyReflector::set_cr(Texture* t_ptr) {
	glossy_specular_brdf->set_cs(t_ptr);
}

//-------------------------------------------------------------- other inline functions
// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
SV_GlossyReflector::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
SV_GlossyReflector::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}

inline void
SV_GlossyReflector::set_cd(Texture* t_ptr)
{
	ambient_brdf->set_cd(t_ptr);
	diffuse_brdf->set_cd(t_ptr);
}

// ---------------------------------------------------------------- set_kd
// this also sets GlossySpecular::exp, but for a different object

inline void								
SV_GlossyReflector::set_exp (const float kd) {
	specular_brdf->set_exp(kd);
}

// ---------------------------------------------------------------- set_ks
// this also sets GlossySpecular::ks, but for a different object

inline void								
SV_GlossyReflector::set_ks (const float kd) {
	specular_brdf->set_ks(kd);
}

// ---------------------------------------------------------------- set_cs

inline void												
SV_GlossyReflector::set_cs(Texture* t_ptr) {
	specular_brdf->set_cs(t_ptr);
}
