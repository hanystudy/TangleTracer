// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "WrappedThreeColors.h"

// I've added the statement that scales value.
// ---------------------------------------------------------------- default constructor

WrappedThreeColors::WrappedThreeColors(void) :max_value(1),min_value(0){}


// ---------------------------------------------------------------- copy constructor

WrappedThreeColors::WrappedThreeColors(const WrappedThreeColors& texture) :max_value(1),min_value(0){}


// ---------------------------------------------------------------- copy constructor

WrappedThreeColors::WrappedThreeColors(LatticeNoise* n) :max_value(1),min_value(0){
	this->noise_ptr = n;
}


// ---------------------------------------------------------------- assignment operator

Texture& 
WrappedThreeColors::operator= (const WrappedThreeColors& rhs) {
	if (this == &rhs)
		return (*this);
		
	return (*this);
}

// ---------------------------------------------------------------- clone

WrappedThreeColors*										
WrappedThreeColors::clone(void) const {
	return (new WrappedThreeColors(*this));
}	


// ---------------------------------------------------------------- destructor

WrappedThreeColors::~WrappedThreeColors(void) {
}

RGBColor														
WrappedThreeColors::get_color(const ShadeRec& sr) const {

	float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;			
	
	if (noise < 1.35) {
		return (value * color1);  
	}
	else if (noise < 2.0) {
		return (value * color2);  
	}
	else {
		return (value * color3);   
	}
	/*
	if (noise < 1.0)
		return (value * color1);
	else
		return (value * color2);*/
}