// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "WrappedFBmTexture.h"

// ---------------------------------------------------------------- default constructor

WrappedFBmTexture::WrappedFBmTexture(void) :
	max_value(1),
	min_value(0),
	expansion_number(0),
	noise_ptr(0),
	color(0)
{}


// ---------------------------------------------------------------- copy constructor

WrappedFBmTexture::WrappedFBmTexture(const WrappedFBmTexture& texture):
	max_value(texture.max_value),
	min_value(texture.min_value),
	expansion_number(texture.expansion_number),
	noise_ptr(texture.noise_ptr),
	color(texture.color)
{
}


// ---------------------------------------------------------------- copy constructor

WrappedFBmTexture::WrappedFBmTexture(LatticeNoise* n) {
	this->noise_ptr = n;
	max_value = 1;
	min_value = 0;
	expansion_number = 0;
	color = RGBColor(0,0,0);
}


// ---------------------------------------------------------------- assignment operator

Texture& 
WrappedFBmTexture::operator= (const WrappedFBmTexture& rhs) {
	if (this == &rhs)
		return (*this);

	this->noise_ptr = rhs.noise_ptr;
	max_value = rhs.max_value;
	min_value = rhs.min_value;
	expansion_number = rhs.expansion_number;
	noise_ptr = rhs.noise_ptr;
	color = rhs.color;
		
	return (*this);
}

// ---------------------------------------------------------------- clone

WrappedFBmTexture*										
WrappedFBmTexture::clone(void) const {
	return (new WrappedFBmTexture(*this));
}	


// ---------------------------------------------------------------- destructor

WrappedFBmTexture::~WrappedFBmTexture(void) {
}


RGBColor 														
WrappedFBmTexture::get_color(const ShadeRec& sr) const {

	float noise = expansion_number * noise_ptr ->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;
	
	return (value * color);
}	
