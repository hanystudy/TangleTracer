#pragma once

// this file contains the declaration of the class ShadeRec

class Material;
class World;	// only need a forward class declaration as the World data member is a reference

#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec {
	public:
	
		bool				hit_an_object;		// did the ray hit an object?
		Point3D				local_hit_point;	// world coordinates of hit point 
		Normal				normal;				// normal at hit point
		RGBColor			color;				// used in Chapter 3 only
		World&				w;					// world reference for shading
		
		Material* 			material_ptr;		// Pointer to the nearest object's material
		Point3D 			hit_point;			// World coordinates of intersection
		Ray					ray;				// Required for specular highlights and area lights
		int					depth;				// recursion depth
		float				t;					// ray parameter

		ShadeRec(World& wr);				// constructor
		
		ShadeRec(const ShadeRec& sr);		// copy constructor
};
