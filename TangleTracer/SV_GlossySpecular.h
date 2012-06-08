// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// this implements textured glossy specular reflection for direct and indirect illumination

#pragma once

#include "BRDF.h"

#include "Texture.h"

class SV_GlossySpecular: public BRDF {
public:

	SV_GlossySpecular(void);

	~SV_GlossySpecular(void);

	virtual SV_GlossySpecular*
		clone(void) const;

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;

	void
		set_ks(const float ks);

	void
		set_exp(const float exp);

	void
		set_cs(Texture* c);

	void
		set_sampler(Sampler* sp, const float exp);   			// any type of sampling

	void
		set_samples(const int num_samples, const float exp); 	// multi jittered sampling

	void
		set_normal(const Normal& n);


private:

	float		ks;
	Texture* 	cs;
	float		exp; 		// specular exponent
	Sampler*	sampler;    // for use in sample_f
};


// -------------------------------------------------------------- set_ks

inline void
	SV_GlossySpecular::set_ks(const float k) {
		ks = k;
}

// -------------------------------------------------------------- set_exp

inline void
	SV_GlossySpecular::set_exp(const float e) {
		exp= e;
}


// -------------------------------------------------------------- set_cs

inline void
	SV_GlossySpecular::set_cs(Texture* c) {
		cs = c;
}
