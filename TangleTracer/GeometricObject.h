// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// this file contains the declaration of the class GeometricObject

#pragma once

#include "RGBColor.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "ShadeRec.h"

#include "BBox.h"

#include "Constants.h"

class Material;

class GeometricObject {	
	
	public:	

		GeometricObject(void);									// default constructor
		
		GeometricObject(const GeometricObject& object);			// copy constructor
	
		virtual GeometricObject*								// virtual copy constructor
		clone(void) const = 0;

		virtual 												// destructor
		~GeometricObject (void);	
			
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
		

		// the following three functions are only required for Chapter 3
		
		void
		set_color(const RGBColor& c);
				
		void
		set_color(const float r, const float g, const float b);
		
		RGBColor
		get_color(void);

		// the follwing functions are worked after chapter 14

		Material*						
		get_material(void) const;

		virtual void 							// needs to virtual so that it can be overriden in Compound
		set_material(Material* mPtr); 			
	
		virtual bool
		shadow_hit(const Ray& ray, float& tmin) const = 0;
		
		virtual void 
		set_bounding_box(void);
		
		virtual BBox 
		get_bounding_box(void);
		
		virtual void 										// required for compound objects
		add_object(GeometricObject* object_ptr);
				
		
		// The following two functions are only required for objects that are light sources, eg disks, rectangles, and spheres
		virtual Point3D 		
		sample(void);
		
		virtual float
		pdf(ShadeRec& sr);
		// The following two functions allow us to simplify the code for smooth shaded triangle meshes
		
		virtual Normal
		get_normal(void) const; 
		
		virtual Normal
		get_normal(const Point3D& p); 

	protected:
	
		RGBColor   color;						// only used for Bare Bones ray tracing
	
		GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);

		mutable Material*   material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
};


// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

// --------------------------------------------------------------------  set_colour

inline void 
GeometricObject::set_color(const float r, const float g, const float b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

// --------------------------------------------------------------------  get_colour

inline RGBColor 
GeometricObject::get_color(void) {
	return (color);
}


// ------------------------------------------------------------------------- get_material

inline Material* 
GeometricObject::get_material(void) const {
	return (material_ptr);
}
