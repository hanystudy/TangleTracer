// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "RampFBmTexture.h"

// ---------------------------------------------------------------- default constructor

RampFBmTexture::RampFBmTexture(void):noise_ptr(NULL) {}


// ---------------------------------------------------------------- copy constructor

RampFBmTexture::RampFBmTexture(const RampFBmTexture& texture):
	ramp_ptr(texture.ramp_ptr),			// this stores the ramp image	
	noise_ptr(texture.noise_ptr),			// supplies the value_fbm noise function
	perturbation(texture.perturbation),		// the amount of fbm ("a" in the book)
	hres(texture.hres)				// horizontal ramp image resolution
{}


// ---------------------------------------------------------------- copy constructor

RampFBmTexture::RampFBmTexture(Image* n):noise_ptr(NULL) {
	this->ramp_ptr = n;
	this->hres = ramp_ptr->get_hres();
}

// ---------------------------------------------------------------- for 31.38 only
RampFBmTexture::RampFBmTexture( Image* n, int c, float d)
{
	this->ramp_ptr = n;
	this->hres = ramp_ptr->get_hres();
	noise_ptr = new CubicNoise(c);
	perturbation = d;
}

// ---------------------------------------------------------------- assignment operator

Texture& 
RampFBmTexture::operator= (const RampFBmTexture& rhs) {
	if (this == &rhs)
		return (*this);

	ramp_ptr = rhs.ramp_ptr;			// this stores the ramp image	
	noise_ptr = rhs.noise_ptr;			// supplies the value_fbm noise function
	perturbation = rhs.perturbation;	// the amount of fbm ("a" in the book)
	hres = rhs.hres;					// horizontal ramp image resolution
		
	return (*this);
}

// ---------------------------------------------------------------- clone

RampFBmTexture*										
RampFBmTexture::clone(void) const {
	return (new RampFBmTexture(*this));
}	


// ---------------------------------------------------------------- destructor

RampFBmTexture::~RampFBmTexture(void) {
}

RGBColor 														
RampFBmTexture::get_color(const ShadeRec& sr) const {
	/*
	float 	y 		= sr.local_hit_point.y;
	float 	u 		= (1.0 + sin(y)) / 2.0;
	int 	row 	= 0;    // use top row of ramp image
	int 	column 	= (int) (u * ( hres - 1));

	return (ramp_ptr->get_color(row, column));
	*/
	// new for list
	float 	noise 	= noise_ptr->value_fbm(sr.local_hit_point);
	float 	y 		= sr.local_hit_point.y + perturbation * noise;
	float 	u 		= (1.0 + sin(y)) / 2.0;
	int 	row 	= 0;    // use top row of ramp image
	int 	column 	= (int) (u * (hres - 1));

	return (ramp_ptr->get_color(row, column));
}
