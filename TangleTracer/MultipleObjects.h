#pragma once

#include "Tracer.h"

class MultipleObjects: public Tracer {
	public:
		
		MultipleObjects(void);							
		
		MultipleObjects(World* _world_ptr);				
	
		virtual											
		~MultipleObjects(void);
						
		virtual RGBColor	
		trace_ray(const Ray& ray) const;
};
