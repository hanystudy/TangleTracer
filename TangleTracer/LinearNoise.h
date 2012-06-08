// 	Copyright (C) Kevin Suffern 2000-2008.
// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class LinearNoise.
// LinearNoise defines the functions value_noise and vector_noise
// using tri-linear interpolation of the lattice noise values.

#pragma once

#include "LatticeNoise.h"

//------------------------------------------------------------------------- class LinearNoise

class LinearNoise: public LatticeNoise
{		
	public: 
	
		LinearNoise(void);								
		
		LinearNoise(int octaves, float lacunarity, float gain);

		LinearNoise(const LinearNoise& lns);		
		
		virtual LinearNoise*											
		clone(void) const;		

		LinearNoise& 										
		operator= (const LinearNoise& rhs);

		virtual
		~LinearNoise(void);								
				
		virtual float											
		value_noise(const Point3D& p) const;
		
		virtual Vector3D 										
		vector_noise(const Point3D& p) const;			
};


//------------------------------------------------------------------------- lerp

// Templated lerp function that can be used for floats and vectors.
// This is not a class member function.

template<class T> T
lerp(const float f, const T& a, const T& b) {
	    return (a + f * (b - a));
}
