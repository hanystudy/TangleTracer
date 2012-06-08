// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class WrappedTwoColors : public Texture	// here you should use public as the qualifier
{
public:

	// constructors etc ...
	WrappedTwoColors(void);										
		
	WrappedTwoColors(const WrappedTwoColors& texture); 			

	WrappedTwoColors(LatticeNoise*);
				
	virtual WrappedTwoColors*									
	clone(void) const;	

	virtual 											
	~WrappedTwoColors(void);

	Texture& 											
	operator= (const WrappedTwoColors& rhs);		
	//
		
	void set_color1(RGBColor c);  

	void set_color2(RGBColor c);

	void set_color1(const float r, const float g, const float b);  

	void set_color2(const float r, const float g, const float b);  

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
	RGBColor color1;
	RGBColor color2;

};

inline void 
WrappedTwoColors::set_color1(RGBColor c)
{
	this->color1 = c;
}

inline void 
WrappedTwoColors::set_color2(RGBColor c)
{
	this->color2 = c;
}

inline void 
WrappedTwoColors::set_min_value(float a)
{
	min_value = a;
}
		
inline void
WrappedTwoColors::set_max_value(float a)
{
	max_value = a;
}

inline void
WrappedTwoColors::set_expansion_number(float e)
{
	this->expansion_number = e;
}

inline void 
WrappedTwoColors::set_color1(const float r, const float g, const float b)
{
	color1 = RGBColor(r,g,b);
}

inline void 
WrappedTwoColors::set_color2(const float r, const float g, const float b)
{
	color2 = RGBColor(r,g,b);
}