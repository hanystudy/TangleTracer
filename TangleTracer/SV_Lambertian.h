// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// this implements textured perfect diffuse scatter

#pragma once

#include "BRDF.h"

#include "Texture.h"

class SV_Lambertian: public BRDF {
public:
	
	SV_Lambertian(void);

	SV_Lambertian(const SV_Lambertian& lamb);

	SV_Lambertian& 
	operator= (const SV_Lambertian& rhs);

	virtual
	~SV_Lambertian(void);

	virtual SV_Lambertian*
	clone(void) const;

	void
	set_kd(const float kd);

	void
	set_cd(Texture* c);

	// constructors, etc ...
	
	virtual RGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
	virtual RGBColor
	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
	
private:
	
	float		kd;
	Texture* 	cd;
};

// -------------------------------------------------------------- set_ka

inline void
SV_Lambertian::set_kd(const float k) {
	kd = k;
}

// -------------------------------------------------------------- set_cd

inline void
SV_Lambertian::set_cd(Texture* c) {
	cd = c;
}
