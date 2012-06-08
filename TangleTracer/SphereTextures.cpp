// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// <math.h> is # included in Texture.h 

#include "Maths.h"
#include "SphereTextures.h"

// ---------------------------------------------------------------- default constructor

SphereTextures::SphereTextures(void)
	:	Texture(),
		num_horizontal_checkers(12),
		num_vertical_checkers(6),
		texture1(NULL),
		texture2(NULL)
{}

// ---------------------------------------------------------------- copy constructor

SphereTextures::SphereTextures(const SphereTextures& sc)
	: 	Texture(sc),
		num_horizontal_checkers(sc.num_horizontal_checkers),
		num_vertical_checkers(sc.num_vertical_checkers),
		texture1(NULL),
		texture2(NULL)
{}


// ---------------------------------------------------------------- assignment operator

SphereTextures& 
SphereTextures::operator= (const SphereTextures& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	Texture::operator=(rhs);
	
	num_horizontal_checkers = rhs.num_horizontal_checkers;
	num_vertical_checkers 	= rhs.num_vertical_checkers;
	texture1 = rhs.texture1;
	texture2 = rhs.texture2;

	return (*this);
}


// ---------------------------------------------------------------- clone

SphereTextures*										
SphereTextures::clone(void) const {
	return (new SphereTextures(*this));
}	


// ---------------------------------------------------------------- destructor

SphereTextures::~SphereTextures(void) {}


// ---------------------------------------------------------------- get_color

RGBColor																				
SphereTextures::get_color(const ShadeRec& sr) const {
	double x = sr.local_hit_point.x;
	double y = sr.local_hit_point.y;
	double z = sr.local_hit_point.z;
		
	double theta = acos(y);
	double phi   = atan2(x, z);
	if (phi < 0.0)
		phi += 2.0 * PI;
	
	double phi_size = 2 * PI / num_horizontal_checkers;   	// in radians - azimuth angle
	double theta_size = PI / num_vertical_checkers;   		// in radians - polar angle
	
	int i_phi 	= floor(phi / phi_size);
	int i_theta = floor(theta / theta_size);
	
	double f_phi 	= phi / phi_size - i_phi;
	double f_theta 	= theta / theta_size - i_theta;
	

	if ((i_phi + i_theta) % 2 == 0) 
	{
		return (texture1->get_color(sr));
	}
	else 
	{
		return (texture2->get_color(sr));
	}
}
	




