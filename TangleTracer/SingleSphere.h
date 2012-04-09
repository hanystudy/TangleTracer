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
