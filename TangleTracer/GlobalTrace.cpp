#include "GlobalTrace.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

GlobalTrace::GlobalTrace(void)
	: Tracer()
{}


// -------------------------------------------------------------------- default constructor
		
GlobalTrace::GlobalTrace(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- trace_ray

RGBColor	
GlobalTrace::trace_ray(const Ray ray, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));  
					
		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			
			return (sr.material_ptr->global_shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}	
}


// -------------------------------------------------------------------- trace_ray
// this version has tmin as an argument, and is used only with the Dielectric material
// for color filtering

RGBColor	
GlobalTrace::trace_ray(const Ray ray, double& tmin, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));  
					
		if (sr.hit_an_object) {
			sr.depth 	= depth;
			sr.ray 		= ray;
			tmin		= sr.t;     // required for colored transparency
			return (sr.material_ptr->global_shade(sr));   
		}
		else{
			tmin = kHugeValue;
			return (world_ptr->background_color);
		}
	}	
}
