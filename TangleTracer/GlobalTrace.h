// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Tracer.h"

class GlobalTrace: public Tracer {
	public:
		
		GlobalTrace(void);
		
		GlobalTrace(World* _worldPtr);
	
		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;
		
		virtual RGBColor	
		trace_ray(const Ray ray, double& tmin, const int depth) const;
};
