// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "stdafx.h"

#include "Material.h"
#include "SV_Lambertian.h"
#include "SV_GlossySpecular.h"

class SV_Phong: public Material {		
	public:
	
		// contructors, etc ...
		SV_Phong(void);											

		SV_Phong(const SV_Phong& m);
		
		virtual Material*										
		clone(void) const;									

		SV_Phong& 
		operator= (const SV_Phong& rhs);							

		~SV_Phong(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);
		
		void													
		set_cd(Texture *c);

		void
		set_exp(const float c);

		void																						
		set_ks(const float c);

		void
		set_cs(Texture *c);
	
		virtual RGBColor									
		shade(ShadeRec& s);	

		virtual void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	
	
	protected:
	
		SV_Lambertian*		ambient_brdf;
		SV_Lambertian*		diffuse_brdf;
		SV_GlossySpecular*	specular_brdf;
};

// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
SV_Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
SV_Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
SV_Phong::set_cd(Texture *c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

// ---------------------------------------------------------------- set_kd
// this also sets GlossySpecular::exp, but for a different object

inline void								
SV_Phong::set_exp (const float kd) {
	specular_brdf->set_exp(kd);
}

// ---------------------------------------------------------------- set_ks
// this also sets GlossySpecular::ks, but for a different object

inline void								
SV_Phong::set_ks (const float kd) {
	specular_brdf->set_ks(kd);
}

// ---------------------------------------------------------------- set_cs

inline void												
SV_Phong::set_cs(Texture *c) {
	specular_brdf->set_cs(c);
}
