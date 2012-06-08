// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This class is from excercise 31.39b which is used similar to WrappedTwoColors class

#pragma once

#include "Texture.h"
#include "LatticeNoise.h"

class WrappedThreeColors : public Texture	// here you should use public as the qualifier
{
public:

	// constructors etc ...
	WrappedThreeColors(void);										
		
	WrappedThreeColors(const WrappedThreeColors& texture); 			

	WrappedThreeColors(LatticeNoise*);
				
	virtual WrappedThreeColors*									
	clone(void) const;	

	virtual 											
	~WrappedThreeColors(void);

	Texture& 											
	operator= (const WrappedThreeColors& rhs);		
	//
		
	void set_color1(RGBColor c);  

	void set_color2(RGBColor c);

	void set_color3(RGBColor c);

	void set_color1(const float r, const float g, const float b);  

	void set_color2(const float r, const float g, const float b);

	void set_color3(const float r, const float g, const float b);  

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
	RGBColor color3;

};

inline void 
WrappedThreeColors::set_color1(RGBColor c)
{
	this->color1 = c;
}

inline void 
WrappedThreeColors::set_color2(RGBColor c)
{
	this->color2 = c;
}

inline void 
WrappedThreeColors::set_min_value(float a)
{
	min_value = a;
}
		
inline void
WrappedThreeColors::set_max_value(float a)
{
	max_value = a;
}

inline void
WrappedThreeColors::set_expansion_number(float e)
{
	this->expansion_number = e;
}

inline void 
WrappedThreeColors::set_color3(RGBColor c)
{
	color3 = c;
}

inline void 
WrappedThreeColors::set_color1(const float r, const float g, const float b)
{
	color1 = RGBColor(r,g,b);	
}

inline void 
WrappedThreeColors::set_color2(const float r, const float g, const float b)
{
	color2 = RGBColor(r,g,b);	
}

inline void 
WrappedThreeColors::set_color3(const float r, const float g, const float b)
{
	color3 = RGBColor(r,g,b);	
}