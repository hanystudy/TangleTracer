// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Texture.h"

// ---------------------------------------------------------------- default constructor

Texture::Texture(void) {}


// ---------------------------------------------------------------- copy constructor

Texture::Texture(const Texture& texture) {}


// ---------------------------------------------------------------- assignment operator

Texture& 
Texture::operator= (const Texture& rhs) {
	if (this == &rhs)
		return (*this);
		
	return (*this);
}


// ---------------------------------------------------------------- destructor

Texture::~Texture(void) {
}



