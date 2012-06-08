// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "RGBColor.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

//-----------------------------------------------------------------------------------class DiskChecker

class DiskChecker: public Texture {		
	public:
	
		DiskChecker(void);					

		DiskChecker(const DiskChecker& sc);
		
		DiskChecker& 												
		operator= (const DiskChecker& rhs);		

		virtual DiskChecker*							
		clone(void) const;				

		~DiskChecker(void);						
		
		virtual RGBColor																				
		get_color(const ShadeRec& sr) const;

		//
		void
		set_num_angular_checkers(const int num_angular);

		void
		set_num_radial_checkers(const int num_radial);

		void
		set_angular_line_width(const float width);

		void
		set_radial_line_width(const float width);
								
		void																	
		set_color1(const float r, const float g, const float b);
		
		void																
		set_color1(const float c);	
		
		void																
		set_color1(const RGBColor& c);
		
		void																	
		set_color2(const float r, const float g, const float b);
		
		void																
		set_color2(const float c);	
		
		void																
		set_color2(const RGBColor& c);									
		
		void																	
		set_line_color(const float r, const float g, const float b); 
		
		void																	
		set_line_color(const float c);
		
		void																
		set_line_color(const RGBColor& c);	
		
		void
		set_radius(const float ra);

		void
		set_center(const Point3D &);

	private:
	
		RGBColor	color1;						// checker color 1
		RGBColor	color2;						// checker color 2
		RGBColor	line_color;					// the line color		

		int num_angular_checkers;     
		int num_radial_checkers;
		float angular_line_width;
		float radial_line_width;
		float radius;
		Point3D center;
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void
DiskChecker::set_num_angular_checkers(const int num_angular)
{
	this->num_angular_checkers = num_angular;
}

inline void
DiskChecker::set_num_radial_checkers(const int num_radial)
{
	this->num_radial_checkers = num_radial;
}

inline void
DiskChecker::set_angular_line_width(const float width)
{
	this->angular_line_width = width;
}

inline void
DiskChecker::set_radial_line_width(const float width)
{
	this->radial_line_width = width;
}
		
inline void																	
DiskChecker::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void																
DiskChecker::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void																
DiskChecker::set_color1(const RGBColor& c) {
color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void																	
DiskChecker::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void																
DiskChecker::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void																
DiskChecker::set_color2(const RGBColor& c) {
color2.r = c.r; color2.g = c.g; color2.b = c.b;
}											

inline void																	
DiskChecker::set_line_color(const float r, const float g, const float b) {
	line_color.r = r; line_color.g = g; line_color.b = b;
}

inline void																	
DiskChecker::set_line_color(const float c) {
	line_color.r = c; line_color.g = c; line_color.b = c;
}

inline void																	
DiskChecker::set_line_color(const RGBColor& c) {
	line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}

inline void
DiskChecker::set_radius(const float ra)
{
	this->radius = ra;
}

inline void
DiskChecker::set_center(const Point3D &p)
{
	this->center = p;
}
