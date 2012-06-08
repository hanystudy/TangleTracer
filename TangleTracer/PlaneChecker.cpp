// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// <math.h> is # included in Texture.h 

#include "Maths.h"
#include "PlaneChecker.h"


// ---------------------------------------------------------------- default constructor

PlaneChecker::PlaneChecker(void)
	:	Texture(),
		outline_width(0.0),
		color1(white),
		color2(0.5),
		outline_color(black),
		size(0)
{}


// ---------------------------------------------------------------- copy constructor

PlaneChecker::PlaneChecker(const PlaneChecker& sc)
	: 	Texture(sc),
		outline_width(sc.outline_width),
		color1(sc.color1),
		color2(sc.color2),
		outline_color(sc.outline_color),
		size(sc.size)
{}


// ---------------------------------------------------------------- assignment operator

PlaneChecker& 
PlaneChecker::operator= (const PlaneChecker& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	Texture::operator=(rhs);
	
	outline_width 	= rhs.outline_width;
	color1			= rhs.color1;
	color2 			= rhs.color2;
	outline_color 	= rhs.outline_color;
	size			= rhs.size;

	return (*this);
}


// ---------------------------------------------------------------- clone

PlaneChecker*										
PlaneChecker::clone(void) const {
	return (new PlaneChecker(*this));
}	


// ---------------------------------------------------------------- destructor

PlaneChecker::~PlaneChecker(void) {}



// ---------------------------------------------------------------- get_color

RGBColor																				
PlaneChecker::get_color(const ShadeRec& sr) const {
	float x = sr.local_hit_point.x;
	float z = sr.local_hit_point.z;
	int ix = floor(x / size);
	int iz = floor(z / size);
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5 * outline_width / size; 
	bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);
	
	if ((ix + iz) % 2 == 0) {
		if (!in_outline)	
			return (color1);
	}
	else {
		if (!in_outline)	
			return (color2);
	}
	
	return (outline_color);
}
	




