// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include <math.h>

#include "Texture.h"

class Checker3D : public Texture {	
	public:
	
		Checker3D(void);										
		
		Checker3D(const Checker3D& texture); 					
				
		virtual Checker3D*									
		clone(void) const;	

		virtual 											
		~Checker3D(void);
		
		virtual RGBColor																			
		get_color(const ShadeRec& sr) const;

		void
		set_color1(const RGBColor&);

		void
		set_color1(const float &, const float &, const float &);

		void
		set_color2(const RGBColor&);

		void
		set_color2(const float &, const float &, const float &);
			
		void
		set_size(const float &);

		Checker3D&
		operator= (const Checker3D& rhs);

	private:
		
		float size;
		RGBColor color1,color2;
};

inline void
Checker3D::set_color1(const RGBColor& c)
{
	color1 = c;
}

inline void
Checker3D::set_color1(const float &r, const float &g, const float &b)
{
	color1 = RGBColor(r,g,b);
}

inline void
Checker3D::set_color2(const RGBColor& c)
{
	color2 = c;
}

inline void
Checker3D::set_color2(const float & r, const float & g, const float & b)
{
	color2 = RGBColor(r,g,b);
}
			
inline void
Checker3D::set_size(const float & s)
{
	size = s;
}
