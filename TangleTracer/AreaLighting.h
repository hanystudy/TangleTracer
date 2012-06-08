// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Tracer.h"

class AreaLighting: public Tracer {
	public:
		
		AreaLighting(void);
		
		AreaLighting(World* _worldPtr);
		
		virtual											
		~AreaLighting(void);	
						
		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;
		
};
