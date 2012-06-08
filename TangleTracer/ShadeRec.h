// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the declaration of the class ShadeRec

#pragma once
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

		float u;	//new for chapter 29
		float v;
};
