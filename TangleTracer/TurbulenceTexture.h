// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class TurbulenceTexture: public Texture {			
	public:
	
		// constructors etc ...
		TurbulenceTexture(void);										
		
		TurbulenceTexture(const TurbulenceTexture& texture); 			

		TurbulenceTexture(LatticeNoise*);
				
		virtual TurbulenceTexture*									
		clone(void) const;	

		virtual 											
		~TurbulenceTexture(void);

		Texture& 											
		operator= (const TurbulenceTexture& rhs);		
		
		void set_color(RGBColor c);  

		void set_color(const float &r, const float &g, const float &b);

		void set_min_value(float);  
		
		void set_max_value(float);
		//
	
		virtual RGBColor 																			
		get_color(const ShadeRec& sr) const;
	
	private:
	
		LatticeNoise*		noise_ptr;
		RGBColor 	  		color;					
		float		  		min_value, max_value;	// scaling factors
};

inline void 
TurbulenceTexture::set_color(RGBColor c)
{
	this->color = c;
}

inline void
TurbulenceTexture::set_color(const float &r, const float &g, const float &b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void 
TurbulenceTexture::set_min_value(float a)
{
	min_value = a;
}
		
inline void
TurbulenceTexture::set_max_value(float a)
{
	max_value = a;
}