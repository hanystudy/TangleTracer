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

//-----------------------------------------------------------------------------------class SphereTextures

class SphereTextures: public Texture {		
	public:
	
		SphereTextures(void);										
		
		SphereTextures(const SphereTextures& sc);
		
		SphereTextures& 												
		operator= (const SphereTextures& rhs);		

		virtual SphereTextures*							
		clone(void) const;				

		~SphereTextures(void);						
		
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
		set_texture1(Texture*);

		void
		set_texture2(Texture*);
		
	private:
	
		int			num_horizontal_checkers;	// number of checkers in the horizontal (azithum) direction
		int			num_vertical_checkers;		// number of checkers in the vertical (polar) direction
		Texture *texture1;
		Texture *texture2;
};


// ---------------------------------------------------------------------------------------------------

// inlined access functions

inline void													
SphereTextures::set_num_horizontal_checkers(const int num_horizontal) {
	num_horizontal_checkers = num_horizontal;
}

inline void													
SphereTextures::set_num_vertical_checkers(const int num_vertical) {
	num_vertical_checkers = num_vertical;
}

// Refer to definition part
inline void
SphereTextures::set_num_vertical(const int num_vertical)
{
	num_vertical_checkers = num_vertical;
}

inline void													
SphereTextures::set_num_horizontal(const int num_horizontal)
{
	num_horizontal_checkers = num_horizontal;
}

//These three functions are used in 22.14

inline void
SphereTextures::set_numlong(const int num)
{
	this->num_horizontal_checkers = num;
}
		
inline void
SphereTextures::set_numlat(const int num)
{
	this->num_vertical_checkers = num;
}
		
inline void
SphereTextures::set_texture1(Texture* a)
{
	this->texture1 = a;
}

inline void
SphereTextures::set_texture2(Texture* b)
{
	this->texture2 = b;
}
