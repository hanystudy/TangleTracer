// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Tracer.h"

class SingleSphere: public Tracer {
	public:
		
		SingleSphere(void);
										
		SingleSphere(World* _worldPtr);					
		
		virtual											
		~SingleSphere(void);
		
		virtual RGBColor	
		trace_ray(const Ray& ray) const;
};
