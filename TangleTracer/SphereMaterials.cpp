// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Maths.h"
#include "SphereMaterials.h"

// ---------------------------------------------------------------- default constructor

SphereMaterials::SphereMaterials(void)
	:	Material(),
		num_horizontal_checkers(20),
		num_vertical_checkers(10),
		horizontal_line_width(0.0),
		vertical_line_width(0.0),
		color1(white),
		color2(0.5),
		line_color(black),
		checker1_m(NULL),
		checker2_m(NULL),
		line_m(NULL)
{}


// ---------------------------------------------------------------- copy constructor

SphereMaterials::SphereMaterials(const SphereMaterials& sc)
	: 	Material(sc),
		num_horizontal_checkers(sc.num_horizontal_checkers),
		num_vertical_checkers(sc.num_vertical_checkers),
		horizontal_line_width(sc.horizontal_line_width),
		vertical_line_width(sc.vertical_line_width),
		color1(sc.color1),
		color2(sc.color2),
		line_color(sc.line_color),
		checker1_m(sc.checker1_m),
		checker2_m(sc.checker2_m),
		line_m(sc.line_m)
{}


// ---------------------------------------------------------------- assignment operator

SphereMaterials& 
SphereMaterials::operator= (const SphereMaterials& rhs) 	
{
	if (this == &rhs)
		return (*this);
	
	Material::operator=(rhs);
	
	num_horizontal_checkers = rhs.num_horizontal_checkers;
	num_vertical_checkers 	= rhs.num_vertical_checkers;
	horizontal_line_width 	= rhs.horizontal_line_width;
	vertical_line_width 	= rhs.vertical_line_width;
	color1					= rhs.color1;
	color2 					= rhs.color2;
	line_color 				= rhs.line_color;

	checker1_m				= rhs.checker1_m;
	checker2_m				= rhs.checker2_m;
	line_m				= rhs.line_m;

	return (*this);
}


// ---------------------------------------------------------------- clone

Material*										
SphereMaterials::clone(void) const {
	return (new SphereMaterials(*this));
}	


// ---------------------------------------------------------------- destructor

SphereMaterials::~SphereMaterials(void) {}

// ---------------------------------------------------------------- shade

RGBColor
SphereMaterials::shade(ShadeRec& sr)
{
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
	
	double phi_line_width = 0.5 * vertical_line_width;
	double theta_line_width = 0.5 * horizontal_line_width;
	
	bool in_outline = (	f_phi < phi_line_width || f_phi > 1.0 - phi_line_width) || 
						(f_theta < theta_line_width || f_theta > 1.0 - theta_line_width);
	
	ShadeRec newsr = sr;

	if ((i_phi + i_theta) % 2 == 0) {
		if (!in_outline)
			return (checker1_m->shade(newsr)/*color1*/);
	}
	else {
		if (!in_outline)
			return (checker2_m->shade(newsr)/*color2*/);
	}
	
	return (line_m->shade(newsr)/*line_color*/);
}

// ---------------------------------------------------------------- get_color

RGBColor																				
SphereMaterials::get_color(const ShadeRec& sr) const {
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
	
	double phi_line_width = 0.5 * vertical_line_width;
	double theta_line_width = 0.5 * horizontal_line_width;
	
	bool in_outline = (	f_phi < phi_line_width || f_phi > 1.0 - phi_line_width) || 
						(f_theta < theta_line_width || f_theta > 1.0 - theta_line_width);
	
	ShadeRec newsr = sr;

	if ((i_phi + i_theta) % 2 == 0) {
		if (!in_outline)
			return (checker1_m->shade(newsr)/*color1*/);
	}
	else {
		if (!in_outline)
			return (checker2_m->shade(newsr)/*color2*/);
	}
	
	return (line_m->shade(newsr)/*line_color*/);
}
	
void									
SphereMaterials::set_ce(const float r, const float g, const float b)
{
	return;
}

RGBColor
SphereMaterials::get_Le(ShadeRec& sr) const
{
	return black;
}
	
RGBColor
SphereMaterials::area_light_shade(ShadeRec& sr)
{
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
	
	double phi_line_width = 0.5 * vertical_line_width;
	double theta_line_width = 0.5 * horizontal_line_width;
	
	bool in_outline = (	f_phi < phi_line_width || f_phi > 1.0 - phi_line_width) || 
						(f_theta < theta_line_width || f_theta > 1.0 - theta_line_width);
	
	ShadeRec newsr = sr;

	if ((i_phi + i_theta) % 2 == 0) {
		if (!in_outline)
			return (checker1_m->shade(newsr)/*color1*/);
	}
	else {
		if (!in_outline)
			return (checker2_m->shade(newsr)/*color2*/);
	}
	
	return (line_m->shade(newsr)/*line_color*/);
}


