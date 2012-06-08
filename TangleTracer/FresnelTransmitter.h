// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "BTDF.h"

class FresnelTransmitter : BTDF
{
public:
	FresnelTransmitter(void);
	
	~FresnelTransmitter(void);
		
	FresnelTransmitter(const FresnelTransmitter& pt);
		
	virtual FresnelTransmitter*
	clone(void);
		
	FresnelTransmitter&							
	operator= (const FresnelTransmitter& rhs);

	bool													
	tir(const ShadeRec& sr) const;
		
	virtual RGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	void
	set_eta_in(const float in);

	void
	set_eta_out(const float out);

	float
	fresnel(const ShadeRec& sr) const;

private:

	float eta_in;
	float eta_out;
};

// -------------------------------------------------------------- set_eta_in

inline void
	FresnelTransmitter::set_eta_in(const float k) {
		eta_in = k;
}

// -------------------------------------------------------------- set_eta_out

inline void
	FresnelTransmitter::set_eta_out(const float k) {
		eta_out = k;
}
