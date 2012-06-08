// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void)
	: world_ptr(NULL)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}



// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = NULL;
}


// -------------------------------------------------------------------- trace_ray

RGBColor	
Tracer::trace_ray(const Ray& ray) const {
	return (black);
}


// -------------------------------------------------------------------- trace_ray

RGBColor	
Tracer::trace_ray(const Ray ray, const int depth) const {
	return (black);
}

// --------------------------------------------------------------------- only for WHitted model

RGBColor	
Tracer::trace_ray(const Ray ray, double &t, const int depth) const
{
	return RGBColor(white);
}
