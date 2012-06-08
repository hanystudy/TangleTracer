// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "stdafx.h"

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong: public Material {		
	public:
	
		// contructors, etc ...
		Phong(void);											

		Phong(const Phong& m);
		
		virtual Material*										
		clone(void) const;									

		Phong& 
		operator= (const Phong& rhs);							

		~Phong(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);
		
		void													
		set_cd(const RGBColor c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void																						
		set_cd(const float c);

		void
		set_exp(const float c);

		void																						
		set_ks(const float c);

		void
		set_cs(const RGBColor& c);

		void													
		set_cs(const float r, const float g, const float b);

		void													
		set_cs(const float c);
	
		virtual RGBColor									
		shade(ShadeRec& s);	

		virtual void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);	
	
		void
		set_shadows(bool);

	protected:
	
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular*	specular_brdf;

		bool shadows;
};

// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Phong::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

// ---------------------------------------------------------------- set_kd
// this also sets GlossySpecular::exp, but for a different object

inline void								
Phong::set_exp (const float kd) {
	specular_brdf->set_exp(kd);
}

// ---------------------------------------------------------------- set_ks
// this also sets GlossySpecular::ks, but for a different object

inline void								
Phong::set_ks (const float kd) {
	specular_brdf->set_ks(kd);
}

// ---------------------------------------------------------------- set_cs

inline void												
Phong::set_cs(const RGBColor &c) {
	specular_brdf->set_cs(c);
}

// ---------------------------------------------------------------- set_cs

inline void													
Phong::set_cs(const float r, const float g, const float b) {
	specular_brdf->set_cs(r, g, b);
}

// ---------------------------------------------------------------- set_cs

inline void													
Phong::set_cs(const float c) {
	specular_brdf->set_cs(c);
}

inline void
Phong::set_shadows(bool b)
{
	this->shadows = b;
}