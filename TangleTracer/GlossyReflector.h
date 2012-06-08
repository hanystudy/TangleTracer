// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Phong.h"

class GlossyReflector: public Phong {	
	public:
	
		// contructors, etc ...
		GlossyReflector(void);											

		GlossyReflector(const GlossyReflector& m);
		
		virtual Material*										
		clone(void) const;									

		GlossyReflector& 
		operator= (const GlossyReflector& rhs);							

		~GlossyReflector(void);											
		
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
	
		// constructors etc ...
	
		void											
		set_samples(const int num_samples, const float exp);

		void
		set_sampler(Sampler *samp, const float exp);
	
		void
		set_kr(const float k);

		void
		set_cr(const float r, const float g, const float b);	//this is new function where doesn't appear in book
			
		void 
		set_cr(const RGBColor r);

		void													
		set_exponent(const float exp);
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);
	
	private:
	
		GlossySpecular* glossy_specular_brdf;

		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
		GlossySpecular*	specular_brdf;
};

inline void
GlossyReflector::set_samples(const int num_samples, const float exp) {
	glossy_specular_brdf->set_samples(num_samples, exp);	
}

inline void
GlossyReflector::set_sampler(Sampler *samp, const float exp)
{
	glossy_specular_brdf->set_sampler(samp, exp);
}

inline void
GlossyReflector::set_kr(const float k) {
	glossy_specular_brdf->set_ks(k);
}
	
inline void
GlossyReflector::set_exponent(const float exp) {
	glossy_specular_brdf->set_exp(exp);
}

inline void
GlossyReflector::set_cr(const float r, const float g, const float b) {
	glossy_specular_brdf->set_cs(r, g, b);
}

//-------------------------------------------------------------- other inline functions
// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
GlossyReflector::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
GlossyReflector::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
GlossyReflector::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
GlossyReflector::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
GlossyReflector::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

// ---------------------------------------------------------------- set_kd
// this also sets GlossySpecular::exp, but for a different object

inline void								
GlossyReflector::set_exp (const float kd) {
	specular_brdf->set_exp(kd);
}

// ---------------------------------------------------------------- set_ks
// this also sets GlossySpecular::ks, but for a different object

inline void								
GlossyReflector::set_ks (const float kd) {
	specular_brdf->set_ks(kd);
}

// ---------------------------------------------------------------- set_cs

inline void												
GlossyReflector::set_cs(const RGBColor &c) {
	specular_brdf->set_cs(c);
}

// ---------------------------------------------------------------- set_cs

inline void													
GlossyReflector::set_cs(const float r, const float g, const float b) {
	specular_brdf->set_cs(r, g, b);
}

// ---------------------------------------------------------------- set_cs

inline void													
GlossyReflector::set_cs(const float c) {
	specular_brdf->set_cs(c);
}

inline void 
GlossyReflector::set_cr(const RGBColor r)
{
	glossy_specular_brdf->set_cs(r);
}