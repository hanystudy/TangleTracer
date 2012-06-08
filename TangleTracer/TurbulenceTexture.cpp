// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "TurbulenceTexture.h"

// ---------------------------------------------------------------- default constructor

TurbulenceTexture::TurbulenceTexture(void) {}


// ---------------------------------------------------------------- copy constructor

TurbulenceTexture::TurbulenceTexture(const TurbulenceTexture& texture) {}


// ---------------------------------------------------------------- copy constructor

TurbulenceTexture::TurbulenceTexture(LatticeNoise* n) {
	this->noise_ptr = n;
}


// ---------------------------------------------------------------- assignment operator

Texture& 
TurbulenceTexture::operator= (const TurbulenceTexture& rhs) {
	if (this == &rhs)
		return (*this);
		
	return (*this);
}

// ---------------------------------------------------------------- clone

TurbulenceTexture*										
TurbulenceTexture::clone(void) const {
	return (new TurbulenceTexture(*this));
}	


// ---------------------------------------------------------------- destructor

TurbulenceTexture::~TurbulenceTexture(void) {
}

RGBColor 														
TurbulenceTexture::get_color(const ShadeRec& sr) const {

	float value = noise_ptr->value_fbm(sr.local_hit_point); // in the range (0, 1)
	value = min_value + (max_value - min_value) * value;	// in the range (min_value, max_value)
	
	return (value * color);
}
