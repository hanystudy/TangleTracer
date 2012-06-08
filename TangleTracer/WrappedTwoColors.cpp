// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "WrappedTwoColors.h"

// I've added the statement that scales value.
// ---------------------------------------------------------------- default constructor

WrappedTwoColors::WrappedTwoColors(void) :max_value(1),min_value(0){}


// ---------------------------------------------------------------- copy constructor

WrappedTwoColors::WrappedTwoColors(const WrappedTwoColors& texture) :max_value(1),min_value(0){}


// ---------------------------------------------------------------- copy constructor

WrappedTwoColors::WrappedTwoColors(LatticeNoise* n) :max_value(1),min_value(0){
	this->noise_ptr = n;
}


// ---------------------------------------------------------------- assignment operator

Texture& 
WrappedTwoColors::operator= (const WrappedTwoColors& rhs) {
	if (this == &rhs)
		return (*this);
		
	return (*this);
}

// ---------------------------------------------------------------- clone

WrappedTwoColors*										
WrappedTwoColors::clone(void) const {
	return (new WrappedTwoColors(*this));
}	


// ---------------------------------------------------------------- destructor

WrappedTwoColors::~WrappedTwoColors(void) {
}

RGBColor														
WrappedTwoColors::get_color(const ShadeRec& sr) const {

	float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;			
	
	if (noise < 1.0)
		return (value * color1);
	else
		return (value * color2);
}