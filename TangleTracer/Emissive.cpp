// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Emissive.h"


// ---------------------------------------------------------------- default constructor

Emissive::Emissive(void) :ls(1.0){}


// ---------------------------------------------------------------- copy constructor

Emissive::Emissive(const Emissive& m) {}



// ---------------------------------------------------------------- assignment operator

Emissive& 
Emissive::operator= (const Emissive& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

Emissive*								
Emissive::clone(void) const
{
	return (new Emissive(*this));
}


// ---------------------------------------------------------------- destructor

Emissive::~Emissive(void)
{}


// ---------------------------------------------------------------- shade

RGBColor
Emissive::shade(ShadeRec& sr) {
	return (black);
}

void
Emissive::scale_radiance(const float _ls)
{
	this->ls = _ls;
}
	
void									
Emissive::set_ce(const float r, const float g, const float b)
{
	ce = RGBColor(r, g, b);
}
		
RGBColor
Emissive::get_Le(ShadeRec& sr) const
{
	return ls * ce;		//here is added, this is very important to multiply ce with ls!!!!!!
}

RGBColor
Emissive::area_light_shade(ShadeRec& sr)
{
	if (-sr.normal * sr.ray.d > 0.0)		//here may be ConcaveSphere not support
		return (ls * ce);
	else
		return (black);
}

RGBColor
Emissive::global_shade(ShadeRec& sr) {	
	if (sr.depth == 1)
		return (black);

	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

RGBColor
Emissive::path_shade(ShadeRec& sr) {		//this new path shade returns final result
	/*
	if (sr.depth == 1)
		return (black);
		*/
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);

}