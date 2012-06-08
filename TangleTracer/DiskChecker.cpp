// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"
#include "DiskChecker.h"

// ---------------------------------------------------------------- default constructor

DiskChecker::DiskChecker(void)
	:	Texture(),
		num_angular_checkers(20),    
		num_radial_checkers(10),
		angular_line_width(0),
		radial_line_width(0),
		color1(white),
		color2(0.5),
		line_color(black),
		radius(1.0),
		center(0.0)
{}

// ---------------------------------------------------------------- copy constructor

DiskChecker::DiskChecker(const DiskChecker& sc)
	: 	Texture(sc),
		num_angular_checkers(sc.num_angular_checkers),    
		num_radial_checkers(sc.num_radial_checkers),
		angular_line_width(sc.angular_line_width),
		radial_line_width(sc.radial_line_width),
		color1(sc.color1),
		color2(sc.color2),
		line_color(sc.line_color),
		radius(sc.radius),
		center(sc.center)
{}


// ---------------------------------------------------------------- assignment operator

DiskChecker& 
DiskChecker::operator= (const DiskChecker& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	Texture::operator=(rhs);
	
	num_angular_checkers	= rhs.num_angular_checkers;    
	num_radial_checkers		= rhs.num_radial_checkers;
	angular_line_width		= rhs.angular_line_width;
	radial_line_width		= rhs.radial_line_width;
	color1					= rhs.color1;
	color2 					= rhs.color2;
	line_color 				= rhs.line_color;
	radius					= rhs.radius;
	center					= rhs.center;

	return (*this);
}


// ---------------------------------------------------------------- clone

DiskChecker*										
DiskChecker::clone(void) const {
	return (new DiskChecker(*this));
}	


// ---------------------------------------------------------------- destructor

DiskChecker::~DiskChecker(void) {}



// ---------------------------------------------------------------- get_color

RGBColor																				
DiskChecker::get_color(const ShadeRec& sr) const {
	double x = sr.local_hit_point.x-center.x;
	double y = sr.local_hit_point.y-center.y;
	double z = sr.local_hit_point.z-center.z;
		
	double phi   = atan2(x, z);
	
	double phi_size = 2 * PI / num_angular_checkers;   	// in radians - azimuth angle
	double theta_size = radius / num_radial_checkers;
	double ra = sqrt(x*x + z*z) / radius;   		// in radians - polar angle

	int i_phi 	= floor(phi / phi_size);
	int i_theta = floor(ra / theta_size);

	double f_phi 	= phi / phi_size - i_phi;
	double f_theta 	= ra / theta_size - i_theta;

	double phi_line_width = 0.5 * angular_line_width;
	double theta_line_width = 0.5 * radial_line_width;
	
	bool in_outline = (	f_phi < phi_line_width || f_phi > 1.0 - phi_line_width) || 
						(f_theta < theta_line_width || f_theta > 1.0 - theta_line_width);
	
	if ((i_phi + i_theta) % 2 == 0) {
		if (!in_outline)
			return (color1);
	}
	else {
		if (!in_outline)
			return (color2);
	}	
	return (line_color);
}
	




