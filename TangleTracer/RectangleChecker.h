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

//-----------------------------------------------------------------------------------class RectangleChecker

class RectangleChecker: public Texture {		
	public:
	
		RectangleChecker(void);					

		RectangleChecker(const RectangleChecker& sc);
		
		RectangleChecker& 												
		operator= (const RectangleChecker& rhs);		

		virtual RectangleChecker*							
		clone(void) const;				

		~RectangleChecker(void);						
		
		virtual RGBColor																				
		get_color(const ShadeRec& sr) const;

		//
		void 
		set_num_x_checkers(const int num_x);

		void 
		set_num_z_checkers(const int num_x);

		void 
		set_x_line_width(const int x_line);

		void 
		set_z_line_width(const int z_line);

		void
		set_p0(const Point3D &p);

		void
		set_a(const Vector3D &v);

		void
		set_b(const Vector3D &v);
		//

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
		
	private:
	
		RGBColor	color1;						// checker color 1
		RGBColor	color2;						// checker color 2
		RGBColor	line_color;					// the line color		

		int num_x_checkers;
		int num_z_checkers;
		float x_line_width;
		float z_line_width;

		Point3D p0;
		Vector3D a;
		Vector3D b;
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void 
RectangleChecker::set_num_x_checkers(const int num_x)
{
	this->num_x_checkers = num_x;
}

inline void 
RectangleChecker::set_num_z_checkers(const int num_x)
{
	this->num_z_checkers = num_x;
}

inline void 
RectangleChecker::set_x_line_width(const int x_line)
{
	this->x_line_width = x_line;
}

inline void 
RectangleChecker::set_z_line_width(const int z_line)
{
	this->z_line_width = z_line;
}

inline void
RectangleChecker::set_p0(const Point3D &p)
{
	this->p0 = p;
}

inline void
RectangleChecker::set_a(const Vector3D &v)
{
	this->a = v;
}

inline void
RectangleChecker::set_b(const Vector3D &v)
{
	b = v;
}

inline void																	
RectangleChecker::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void																
RectangleChecker::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void																
RectangleChecker::set_color1(const RGBColor& c) {
color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void																	
RectangleChecker::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void																
RectangleChecker::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void																
RectangleChecker::set_color2(const RGBColor& c) {
color2.r = c.r; color2.g = c.g; color2.b = c.b;
}											

inline void																	
RectangleChecker::set_line_color(const float r, const float g, const float b) {
	line_color.r = r; line_color.g = g; line_color.b = b;
}

inline void																	
RectangleChecker::set_line_color(const float c) {
	line_color.r = c; line_color.g = c; line_color.b = c;
}

inline void																	
RectangleChecker::set_line_color(const RGBColor& c) {
	line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}
