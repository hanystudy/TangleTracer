// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// Notice that the original resource didn't give a initial value of texture color, while in exercise 29.11b it seems that SV_Phong uses this white color as default, so we have added this feature into the code

#pragma once

#include "Texture.h"

class ConstantColor: public Texture {		
	public:
		
		ConstantColor(void);										
		
		ConstantColor(const ConstantColor& texture); 					
		
		ConstantColor(RGBColor c);

		virtual ConstantColor*									
		clone(void) const;	

		virtual 											
		~ConstantColor(void);

		// constructors etc
		
		void
		set_color(const RGBColor& c); 
		
		virtual RGBColor														
		get_color(const ShadeRec& sr) const;
	
	protected:

		ConstantColor& 											
		operator= (const ConstantColor& rhs);

	private:
		
		RGBColor color;	 // the color		
};
		
		
inline RGBColor
ConstantColor::get_color(const ShadeRec& sr) const {
	return (color);
}

inline void
ConstantColor::set_color(const RGBColor& c) {
	color = c;
}