// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class FBmTexture: public Texture {			
	public:
	
		// constructors etc ...
		FBmTexture(void);										
		
		FBmTexture(const FBmTexture& texture); 			

		FBmTexture(LatticeNoise*);
				
		virtual FBmTexture*									
		clone(void) const;	

		virtual 											
		~FBmTexture(void);

		Texture& 											
		operator= (const FBmTexture& rhs);		
		
		void set_color(RGBColor c);  

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
FBmTexture::set_color(RGBColor c)
{
	this->color = c;
}

inline void 
FBmTexture::set_min_value(float a)
{
	min_value = a;
}
		
inline void
FBmTexture::set_max_value(float a)
{
	max_value = a;
}