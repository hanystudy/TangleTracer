// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "RGBColor.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

//-----------------------------------------------------------------------------------class PlaneChecker

class PlaneChecker: public Texture {		
	public:
	
		PlaneChecker(void);										
		
		PlaneChecker(const PlaneChecker& sc);
		
		PlaneChecker& 												
		operator= (const PlaneChecker& rhs);		

		virtual PlaneChecker*							
		clone(void) const;				

		~PlaneChecker(void);						
		
		virtual RGBColor																				
		get_color(const ShadeRec& sr) const;
				
		void													
		set_size(const float s);
		
		void													
		set_outline_width(const float width);
								
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
		set_outline_color(const float r, const float g, const float b); 
		
		void																	
		set_outline_color(const float c);
		
		void																
		set_outline_color(const RGBColor& c);	

	private:
	
		float		outline_width;		// width of the horizontal lines as a fraction of the checker width
		RGBColor	color1;						// checker color 1
		RGBColor	color2;						// checker color 2
		RGBColor	outline_color;					// the line color		
		float size;
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void													
PlaneChecker::set_outline_width(const float width) {
	outline_width = width;
}
		
inline void																	
PlaneChecker::set_color1(const float r, const float g, const float b) {
	color1.r = r; color1.g = g; color1.b = b;
}

inline void																
PlaneChecker::set_color1(const float c) {
	color1.r = c; color1.g = c; color1.b = c;
}

inline void																
PlaneChecker::set_color1(const RGBColor& c) {
color1.r = c.r; color1.g = c.g; color1.b = c.b;
}

inline void																	
PlaneChecker::set_color2(const float r, const float g, const float b) {
	color2.r = r; color2.g = g; color2.b = b;
}

inline void																
PlaneChecker::set_color2(const float c) {
	color2.r = c; color2.g = c; color2.b = c;
}

inline void																
PlaneChecker::set_color2(const RGBColor& c) {
color2.r = c.r; color2.g = c.g; color2.b = c.b;
}											

inline void																	
PlaneChecker::set_outline_color(const float r, const float g, const float b) {
	outline_color.r = r; outline_color.g = g; outline_color.b = b;
}

inline void																	
PlaneChecker::set_outline_color(const float c) {
	outline_color.r = c; outline_color.g = c; outline_color.b = c;
}

inline void																	
PlaneChecker::set_outline_color(const RGBColor& c) {
	outline_color.r = c.r; outline_color.g = c.g; outline_color.b = c.b;
}

inline void													
PlaneChecker::set_size(const float s) {
	size = s ;
}