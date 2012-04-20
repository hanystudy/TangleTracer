#pragma once

#include "Tracer.h"

class RayCast: public Tracer {
	public:
		
		RayCast(void);
		
		RayCast(World* _worldPtr);
				
		virtual											
		~RayCast(void);		

		virtual RGBColor	
		trace_ray(const Ray& ray) const;

		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;
};
