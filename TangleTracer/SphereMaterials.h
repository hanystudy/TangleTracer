// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// Note: The SphereMaterials class contains three kinds of materials in all,
// which is different from the past one that only returns pure color, 
// I implemented this according to excercise 24.15c

#pragma once

#include "Material.h"
#include "RGBColor.h"

//-----------------------------------------------------------------------------------class SphereMaterials

class SphereMaterials: public Material {		
	public:
	
		SphereMaterials(void);										
		
		SphereMaterials(const SphereMaterials& sc);
		
		SphereMaterials& 												
		operator= (const SphereMaterials& rhs);		

		virtual Material*							
		clone(void) const;				

		~SphereMaterials(void);						
		
		virtual RGBColor																				
		get_color(const ShadeRec& sr) const;
				
		void													
		set_num_horizontal_checkers(const int num_horizontal);
		
		void													
		set_num_vertical_checkers(const int num_vertical);

		//These two functios below are needed by 20.06
		void
		set_num_vertical(const int num_vertical);

		void													
		set_num_horizontal(const int num_horizontal);

		//These three functions below are needed by 22.14
		void
		set_numlong(const int num);
		
		void
		set_numlat(const int num);
		
		void
		set_line_width(const float wid);
		
		void													
		set_horizontal_line_width(const float width);
		
		void													
		set_vertical_line_width(const float width);
								
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

		virtual void									
		set_ce(const float r, const float g, const float b);
		
		virtual RGBColor
		get_Le(ShadeRec& sr) const;	
	
		virtual RGBColor
		area_light_shade(ShadeRec& sr);

		void
		set_checker1_material(Material *m);

		void
		set_checker2_material(Material *m);

		void
		set_line_material(Material *m);

		virtual RGBColor
		shade(ShadeRec& sr);	

	private:
	
		int			num_horizontal_checkers;	// number of checkers in the horizontal (azithum) direction
		int			num_vertical_checkers;		// number of checkers in the vertical (polar) direction
		float		horizontal_line_width;		// width of the horizontal lines as a fraction of the checker width
		float		vertical_line_width;		// width of the vertical lines as a fraction of the checker width
		RGBColor	color1;						// checker color 1
		RGBColor	color2;						// checker color 2
		RGBColor	line_color;					// the line color							

		Material *checker1_m;
		Material *checker2_m;
		Material *line_m;

};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void													
SphereMaterials::set_num_horizontal_checkers(const int num_horizontal) {
	num_horizontal_checkers = num_horizontal;
}

inline void													
SphereMaterials::set_num_vertical_checkers(const int num_vertical) {
	num_vertical_checkers = num_vertical;
}

// Refer to definition part
inline void
SphereMaterials::set_num_vertical(const int num_vertical)
{
	num_vertical_checkers = num_vertical;
}

inline void													
SphereMaterials::set_num_horizontal(const int num_horizontal)
{
	num_horizontal_checkers = num_horizontal;
}

//These three functions are used in 22.14

inline void
SphereMaterials::set_numlong(const int num)
{
	this->num_horizontal_checkers = num;
}
		
inline void
SphereMaterials::set_numlat(const int num)
{
	this->num_vertical_checkers = num;
}
		
inline void
SphereMaterials::set_line_width(const float wid)
{
	horizontal_line_width = wid;
	vertical_line_width = wid;
}

inline void													
SphereMaterials::set_horizontal_line_width(const float width) {
	horizontal_line_width = width;
}

inline void													
SphereMaterials::set_vertical_line_width(const float width) {
	vertical_line_width = width;
}
		
inline void																	
SphereMaterials::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void																
SphereMaterials::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void																
SphereMaterials::set_color1(const RGBColor& c) {
color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void																	
SphereMaterials::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void																
SphereMaterials::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void																
SphereMaterials::set_color2(const RGBColor& c) {
color2.r = c.r; color2.g = c.g; color2.b = c.b;
}											

inline void																	
SphereMaterials::set_line_color(const float r, const float g, const float b) {
	line_color.r = r; line_color.g = g; line_color.b = b;
}

inline void																	
SphereMaterials::set_line_color(const float c) {
	line_color.r = c; line_color.g = c; line_color.b = c;
}

inline void																	
SphereMaterials::set_line_color(const RGBColor& c) {
	line_color.r = c.r; line_color.g = c.g; line_color.b = c.b;
}

inline void
SphereMaterials::set_checker1_material(Material *m)
{
	checker1_m = m;
}

inline void
SphereMaterials::set_checker2_material(Material *m)
{
	checker2_m = m;
}

inline void
SphereMaterials::set_line_material(Material *m)
{
	line_m = m;
}
