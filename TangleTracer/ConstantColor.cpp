// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "ConstantColor.h"

// ---------------------------------------------------------------- default constructor

ConstantColor::ConstantColor(void) {
	this->color = RGBColor(1.0,1.0,1.0);	// Here we give white color for default color
}


// ---------------------------------------------------------------- copy constructor

ConstantColor::ConstantColor(const ConstantColor& texture):
color(texture.color){}

// ------------ for 31.29a only

ConstantColor::ConstantColor(RGBColor c)
{
	this->color =c;
}


// ---------------------------------------------------------------- assignment operator

ConstantColor& 
ConstantColor::operator= (const ConstantColor& rhs) {
	if (this == &rhs)
		return (*this);

	color = rhs.color;
		
	return (*this);
}


// ---------------------------------------------------------------- destructor

ConstantColor::~ConstantColor(void) {
}

// ---------------------------------------------------------------- clone
ConstantColor*									
ConstantColor::clone(void) const {
	
	return (new ConstantColor(*this));
}
