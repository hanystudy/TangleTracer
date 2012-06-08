// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Checker3D.h"
#include "Constants.h"

// ---------------------------------------------------------------- default constructor

Checker3D::Checker3D(void):size(0),color1(white),color2(white) {}


// ---------------------------------------------------------------- copy constructor

Checker3D::Checker3D(const Checker3D& texture):size(texture.size),color1(texture.color1),color2(texture.color2) {}


// ---------------------------------------------------------------- assignment operator

Checker3D& 
Checker3D::operator= (const Checker3D& rhs) {
	if (this == &rhs)
		return (*this);

	size = rhs.size;
	color1 = rhs.color1;
	color2 = rhs.color2;
		
	return (*this);
}


// ---------------------------------------------------------------- destructor

Checker3D::~Checker3D(void) {
}


// ---------------------------------------------------------------- clone
Checker3D*									
Checker3D::clone(void) const {
	
	return (new Checker3D(*this));
}

RGBColor														
Checker3D::get_color(const ShadeRec& sr) const {	
	
	float eps = -0.000187453738;	// small random number
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;		
	
	if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)	
		return (color1);
	else	
		return (color2);
}