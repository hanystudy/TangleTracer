// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class WrappedFBmTexture : public Texture
{
public:

	// constructors etc ...
	WrappedFBmTexture(void);										
		
	WrappedFBmTexture(const WrappedFBmTexture& texture); 			

	WrappedFBmTexture(LatticeNoise*);
				
	virtual WrappedFBmTexture*									
	clone(void) const;	

	virtual 											
	~WrappedFBmTexture(void);

	Texture& 											
	operator= (const WrappedFBmTexture& rhs);		
	//
		
	void set_color(RGBColor c);  

	void set_color(const float r, const float g, const float b);

	void set_min_value(float);  
		
	void set_max_value(float);

	void set_expansion_number(float);
	//

	RGBColor
	get_color(const ShadeRec& sr) const;

private:
	float max_value;
	float min_value;
	float expansion_number;
	LatticeNoise *noise_ptr;
	RGBColor color;
};

inline void 
WrappedFBmTexture::set_color(RGBColor c)
{
	this->color = c;
}

inline void
WrappedFBmTexture::set_color(const float r, const float g, const float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void 
WrappedFBmTexture::set_min_value(float a)
{
	min_value = a;
}
		
inline void
WrappedFBmTexture::set_max_value(float a)
{
	max_value = a;
}

inline void
WrappedFBmTexture::set_expansion_number(float e)
{
	this->expansion_number = e;
}