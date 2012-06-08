// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"
#include "RectangleChecker.h"

// ---------------------------------------------------------------- default constructor

RectangleChecker::RectangleChecker(void)
	:	Texture(),
		num_x_checkers(20),
		num_z_checkers(20),
		x_line_width(0),
		z_line_width(0),
		color1(white),
		color2(0.5),
		line_color(black),
		p0(Point3D(-1,0,-1)),
		a(Vector3D(0,0,2)),
		b(Vector3D(2,0,0))
{}

// ---------------------------------------------------------------- copy constructor

RectangleChecker::RectangleChecker(const RectangleChecker& sc)
	: 	Texture(sc),
		num_x_checkers(sc.num_x_checkers),
		num_z_checkers(sc.num_z_checkers),
		x_line_width(sc.x_line_width),
		z_line_width(sc.z_line_width),
		color1(sc.color1),
		color2(sc.color2),
		line_color(sc.line_color),
		p0(sc.p0),
		a(sc.a),
		b(sc.b)
{}

// ---------------------------------------------------------------- assignment operator

RectangleChecker& 
RectangleChecker::operator= (const RectangleChecker& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	Texture::operator=(rhs);
	
	num_x_checkers = rhs.num_x_checkers;
	num_z_checkers = rhs.num_z_checkers;
	x_line_width = rhs.x_line_width;
	z_line_width = rhs.z_line_width;
	color1 = rhs.color1;
	color2 = rhs.color2;
	line_color = rhs.line_color;
	p0 = rhs.p0;
	a = rhs.a;
	b = rhs.b;

	return (*this);
}


// ---------------------------------------------------------------- clone

RectangleChecker*										
RectangleChecker::clone(void) const {
	return (new RectangleChecker(*this));
}	


// ---------------------------------------------------------------- destructor

RectangleChecker::~RectangleChecker(void) {}



// ---------------------------------------------------------------- get_color

RGBColor																				
RectangleChecker::get_color(const ShadeRec& sr) const {
	double x = sr.local_hit_point.x;
	double y = sr.local_hit_point.y;
	double z = sr.local_hit_point.z;

	double x_size = b.x / num_x_checkers;   	// in radians - azimuth angle
	double z_size = a.z /num_z_checkers;
	
	int i_phi 	= floor(x / x_size);
	int i_theta = floor(z / z_size);

	double f_phi 	= x / x_size - i_phi;
	double f_theta 	= z / z_size - i_theta;

	double phi_line_width = 0.5 * x_line_width;
	double theta_line_width = 0.5 * z_line_width;
	
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
	




