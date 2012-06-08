// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class NestedNoisesTexture : public Texture	// here you should use public as the qualifier
{
public:

	// constructors etc ...
	NestedNoisesTexture(void);										
		
	NestedNoisesTexture(const NestedNoisesTexture& texture); 			

	NestedNoisesTexture(LatticeNoise*);
				
	virtual NestedNoisesTexture*									
	clone(void) const;	

	virtual 											
	~NestedNoisesTexture(void);

	Texture& 											
	operator= (const NestedNoisesTexture& rhs);		
	//
		
	void set_color(RGBColor c);  

	void set_color(const float r, const float g, const float b);  

	void set_min_value(float);  
		
	void set_max_value(float);

	void set_expansion_number(float);

	void set_wrap_factor(float);

	void set_texture(Texture*);
	//

	RGBColor
	get_color(const ShadeRec& sr) const;

private:
	float max_value;
	float min_value;
	float expansion_number;
	float wrap_factor;
	LatticeNoise *noise_ptr;
	RGBColor color1;
	Texture *texture_ptr;

};

inline void 
NestedNoisesTexture::set_color(RGBColor c)
{
	this->color1 = c;
}

inline void 
NestedNoisesTexture::set_min_value(float a)
{
	min_value = a;
}
		
inline void
NestedNoisesTexture::set_max_value(float a)
{
	max_value = a;
}

inline void
NestedNoisesTexture::set_expansion_number(float e)
{
	this->expansion_number = e;
}

inline void 
NestedNoisesTexture::set_color(const float r, const float g, const float b)
{
	color1 = RGBColor(r,g,b);
}

inline void 
NestedNoisesTexture::set_wrap_factor(float f)
{
	wrap_factor = f;
}

inline void 
NestedNoisesTexture::set_texture(Texture* t)
{
	texture_ptr = t;
}
