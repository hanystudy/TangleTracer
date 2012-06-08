// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "BRDF.h"

#include "Normal.h"

class FresnelReflector: public BRDF 
{
public:

	FresnelReflector(void);

	~FresnelReflector(void);

	virtual FresnelReflector*
		clone(void) const;

	void
		set_cr(const RGBColor& c);

	void													
		set_cr(const float r, const float g, const float b);

	void													
		set_cr(const float c);

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const;

	float
		fresnel(const ShadeRec& sr) const;

	void
		set_eta_in(const float in);

	void
		set_eta_out(const float out);

private:

	float eta_in;
	float eta_out;
	RGBColor 	cr;			// the reflection colour
};


// -------------------------------------------------------------- set_eta_in

inline void
	FresnelReflector::set_eta_in(const float k) {
		eta_in = k;
}

// -------------------------------------------------------------- set_eta_out

inline void
	FresnelReflector::set_eta_out(const float k) {
		eta_out = k;
}


// -------------------------------------------------------------- set_cr

inline void
	FresnelReflector::set_cr(const RGBColor& c) {
		cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void													
	FresnelReflector::set_cr(const float r, const float g, const float b) {
		cr.r = r; cr.g = g; cr.b = b;
}


// ---------------------------------------------------------------- set_cr

inline void													
	FresnelReflector::set_cr(const float c) {
		cr.r = c; cr.g = c; cr.b = c;
}