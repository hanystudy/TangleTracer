// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "NestedNoisesTexture.h"

// I've added the statement that scales value.
// ---------------------------------------------------------------- default constructor

NestedNoisesTexture::NestedNoisesTexture(void) :max_value(1),min_value(0),texture_ptr(0){}


// ---------------------------------------------------------------- copy constructor

NestedNoisesTexture::NestedNoisesTexture(const NestedNoisesTexture& texture) :max_value(texture.max_value),min_value(texture.min_value),texture_ptr(texture.texture_ptr){}


// ---------------------------------------------------------------- copy constructor

NestedNoisesTexture::NestedNoisesTexture(LatticeNoise* n) :max_value(1),min_value(0),texture_ptr(0){
	this->noise_ptr = n;
}


// ---------------------------------------------------------------- assignment operator

Texture& 
NestedNoisesTexture::operator= (const NestedNoisesTexture& rhs) {
	if (this == &rhs)
		return (*this);
		
	max_value = rhs.max_value;
	min_value = rhs.min_value;
	texture_ptr = rhs.texture_ptr;

	return (*this);
}

// ---------------------------------------------------------------- clone

NestedNoisesTexture*										
NestedNoisesTexture::clone(void) const {
	return (new NestedNoisesTexture(*this));
}	


// ---------------------------------------------------------------- destructor

NestedNoisesTexture::~NestedNoisesTexture(void) {
}

RGBColor														
NestedNoisesTexture::get_color(const ShadeRec& sr) const {
	/*
	float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;			
	
	if (noise < 1.0)
		return (value * color1);
	else
		return (value * color2);*/
	float noise = wrap_factor * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = (max_value - min_value) * value + min_value;
	
	if (noise < 1.0)
		return (value * color1);
	else
		return (value * texture_ptr->get_color(sr));
}