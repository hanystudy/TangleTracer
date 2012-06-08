// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"
#include "Image.h"

class WrappedRamp : public Texture
{
public:

	// constructors etc ...
	WrappedRamp(void);										
		
	WrappedRamp(const WrappedRamp& texture); 			

	WrappedRamp(LatticeNoise*);

	WrappedRamp(Image*);
				
	virtual WrappedRamp*									
	clone(void) const;	

	virtual 											
	~WrappedRamp(void);

	Texture& 											
	operator= (const WrappedRamp& rhs);		
	//
		
	void set_color(RGBColor c);  

	void set_color(const float r, const float g, const float b);

	void set_min_value(float);  
		
	void set_max_value(float);

	void set_expansion_number(float);
	//
	void set_noise(LatticeNoise*);
	
	void set_perturbation(float);
	
	void set_wrap_number(float);

	RGBColor
	get_color(const ShadeRec& sr) const;

private:
	float max_value;
	float min_value;
	float expansion_number;
	LatticeNoise *noise_ptr;
	RGBColor color;
	Image *image_ptr;
	float perturbation;
	float wrap_number;
	int hres;
};

inline void 
WrappedRamp::set_color(RGBColor c)
{
	this->color = c;
}

inline void
WrappedRamp::set_color(const float r, const float g, const float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void 
WrappedRamp::set_min_value(float a)
{
	min_value = a;
}
		
inline void
WrappedRamp::set_max_value(float a)
{
	max_value = a;
}

inline void
WrappedRamp::set_expansion_number(float e)
{
	this->expansion_number = e;
}

//
inline void 
WrappedRamp::set_noise(LatticeNoise* noise)
{
	if( noise_ptr != NULL)
		delete noise_ptr;
	this->noise_ptr = noise;
}
	
inline void 
WrappedRamp::set_perturbation(float per)
{
	perturbation = per;
}
	
inline void 
WrappedRamp::set_wrap_number(float wrap)
{
	wrap_number = wrap;
}
