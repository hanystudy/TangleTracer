// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "WrappedRamp.h"

// ---------------------------------------------------------------- default constructor

WrappedRamp::WrappedRamp(void) :
	max_value(1),
	min_value(0),
	expansion_number(0),
	noise_ptr(0),
	color(0),
	image_ptr(0)
{}


// ---------------------------------------------------------------- copy constructor

WrappedRamp::WrappedRamp(const WrappedRamp& texture):
	max_value(texture.max_value),
	min_value(texture.min_value),
	expansion_number(texture.expansion_number),
	noise_ptr(texture.noise_ptr),
	color(texture.color),
	image_ptr(texture.image_ptr)
{
}


// ---------------------------------------------------------------- copy constructor

WrappedRamp::WrappedRamp(LatticeNoise* n) {
	this->noise_ptr = n;
	max_value = 1;
	min_value = 0;
	expansion_number = 0;
	color = RGBColor(0,0,0);
}

// --------------------------------------------------------------- another constructor

WrappedRamp::WrappedRamp(Image* image)
{
	image_ptr = image;
	this->noise_ptr = 0;
	max_value = 1;
	min_value = 0;
	expansion_number = 0;
	color = RGBColor(0,0,0);
	hres = image->get_hres();
}

// ---------------------------------------------------------------- assignment operator

Texture& 
WrappedRamp::operator= (const WrappedRamp& rhs) {
	if (this == &rhs)
		return (*this);

	this->noise_ptr = rhs.noise_ptr;
	max_value = rhs.max_value;
	min_value = rhs.min_value;
	expansion_number = rhs.expansion_number;
	noise_ptr = rhs.noise_ptr;
	color = rhs.color;
	image_ptr = rhs.image_ptr;
		
	return (*this);
}

// ---------------------------------------------------------------- clone

WrappedRamp*										
WrappedRamp::clone(void) const {
	return (new WrappedRamp(*this));
}	


// ---------------------------------------------------------------- destructor

WrappedRamp::~WrappedRamp(void) {
}


RGBColor 														
WrappedRamp::get_color(const ShadeRec& sr) const {

	float 	noise 	= wrap_number* noise_ptr->value_fbm(sr.local_hit_point);
	float 	y 		= sr.local_hit_point.y + perturbation * noise;
	float 	u 		= (1.0 + sin(y)) / 2.0;
	int 	row 	= 0;    // use top row of ramp image
	int 	column 	= (int) (u * (hres - 1));

	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;

	return (value * image_ptr->get_color(row, column));
	/*
	float noise = expansion_number * noise_ptr ->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;	
	return (value * color);
	*/
}	
