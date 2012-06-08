// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include <math.h>

#include "Point3D.h"

class Mapping {		
	public:
		
		Mapping(void);										
		
		Mapping(const Mapping& m);							

		Mapping& 											
		operator= (const Mapping& rhs);		

		virtual Mapping*									
		clone(void) const = 0;				

		virtual ~Mapping(void);								
				
		virtual void
		get_texel_coordinates(	const 	Point3D& 	hit_point, 
								const 	int 		xres, 
								const 	int 		yres, 
										int& 		row, 
										int& 		column) const = 0;
};
